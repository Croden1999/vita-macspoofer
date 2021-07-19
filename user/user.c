#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/registrymgr.h>
#include <psp2/system_param.h>
#include <taihen.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "language.h"

#define CONFIG_PATH "ur0:tai/macspoofer.cfg"

extern unsigned char _binary_security_settings_xml_start;
extern unsigned char _binary_security_settings_xml_size;

static SceUID g_hooks[11];

typedef struct cfg_struct {
  uint8_t enable_mac_spoofing;
  uint8_t styleformat;
  uint8_t enable_customtext;
  char custom_text[18];
} __attribute__((packed)) cfg_struct;

static cfg_struct config;
static void save_config_user(void) {
  SceUID fd;
  fd = sceIoOpen(CONFIG_PATH, SCE_O_TRUNC | SCE_O_CREAT | SCE_O_WRONLY, 6);
  if (fd >= 0) {
    sceIoWrite(fd, &config, sizeof(config));
    sceIoClose(fd);
  }
}

static int load_config_user(void) {
  SceUID fd;
  int rd;
  fd = sceIoOpen(CONFIG_PATH, SCE_O_RDONLY, 0);
  if (fd >= 0) {
    rd = sceIoRead(fd, &config, sizeof(config));
    sceIoClose(fd);
    if (rd == sizeof(config))
      return 0;
  }
  //default config
  sceClibMemset(&config, 0, sizeof(config));
    config.enable_mac_spoofing = 1;
    config.styleformat = 1;
    config.enable_customtext = 0;
    sceClibMemset(config.custom_text, 0, 18);
    sceClibStrncpy(config.custom_text, "[HIDDEN]", 8);
  save_config_user();
  return 0;
}

static tai_hook_ref_t g_scePafMiscLoadXmlLayout_SceSettings_hook;
static int scePafMiscLoadXmlLayout_SceSettings_patched(int a1, void *xml_buf, int xml_size, int a4) {
  if( (82+24) < xml_size && sceClibStrncmp(xml_buf+82, "security_settings_plugin", 24) == 0 ) { //
    xml_buf = (void *)&_binary_security_settings_xml_start;
    xml_size = (int)&_binary_security_settings_xml_size;
  }
  return TAI_CONTINUE(int, g_scePafMiscLoadXmlLayout_SceSettings_hook, a1, xml_buf, xml_size, a4);
}

static tai_hook_ref_t g_sce_paf_private_snprintf_SceSettings_hook;
static int sce_paf_private_snprintf_SceSettings_patched(char *s, size_t n, const char *format, ...) {
  if (n == 18 && sceClibStrncmp(format, "%02X:%02X:%02X:%02X:%02X:%02X", 18) == 0) {
    if (config.enable_mac_spoofing == 1) {
      sceClibMemset(s, 0, n);
      if (config.enable_customtext == 1) {
        sceClibStrncpy(s, config.custom_text, 18);
      } else {
        switch(config.styleformat) {
          case 0: sceClibStrncpy(s, "00:00:00:00:00:00", 18); break;
          case 1: sceClibStrncpy(s, "XX:XX:XX:XX:XX:XX", 18); break;
          case 2: sceClibStrncpy(s, "??:??:??:??:??:??", 18); break;
          case 3: sceClibStrncpy(s, "##:##:##:##:##:##", 18); break;
          case 4: sceClibStrncpy(s, "--:--:--:--:--:--", 18); break;
          default: sceClibStrncpy(s, "error", 5); break;
        }
      }
      return 0;
    }
  }

  va_list list;
  va_start(list, format);
  int res = sceClibVsnprintf(s, n, format, list);
  va_end(list);

  return res;
}

static tai_hook_ref_t g_sceRegMgrGetKeyInt_SceSystemSettingsCore_hook;
static int sceRegMgrGetKeyInt_SceSystemSettingsCore_patched(const char *category, const char *name, int *value) {
  if (sceClibStrncmp(category, "/CONFIG/MACSPOOF", 16) == 0) {
    if (value) {
      load_config_user();
      if (sceClibStrncmp(name, "enable_mac_spoofing", 19) == 0) {
        *value = config.enable_mac_spoofing;
      } else if (sceClibStrncmp(name, "styleformat", 11) == 0) {
        *value = config.styleformat;
      } else if (sceClibStrncmp(name, "enable_customtext", 17) == 0) {
        *value = config.enable_customtext;
      }
    }
    save_config_user();
    return 0;
  }
  return TAI_CONTINUE(int, g_sceRegMgrGetKeyInt_SceSystemSettingsCore_hook, category, name, value);
}

static tai_hook_ref_t g_sceRegMgrSetKeyInt_SceSystemSettingsCore_hook;
static int sceRegMgrSetKeyInt_SceSystemSettingsCore_patched(const char *category, const char *name, int value) {
  if (sceClibStrncmp(category, "/CONFIG/MACSPOOF", 16) == 0) {
    if (sceClibStrncmp(name, "enable_mac_spoofing", 19) == 0) {
      config.enable_mac_spoofing = value;
    } else if (sceClibStrncmp(name, "styleformat", 11) == 0) {
      config.styleformat = value;
    } else if (sceClibStrncmp(name, "enable_customtext", 17) == 0) {
      config.enable_customtext = value;
    }
    save_config_user();
    //henkaku_reload_config();
    return 0;
  }
  return TAI_CONTINUE(int, g_sceRegMgrSetKeyInt_SceSystemSettingsCore_hook, category, name, value);
}

static tai_hook_ref_t g_sceRegMgrGetKeyStr_SceSystemSettingsCore_hook;
static int sceRegMgrGetKeyStr_SceSystemSettingsCore_patched(const char *category, const char *name, char *string, int length) {
  if (sceClibStrncmp(category, "/CONFIG/MACSPOOF", 16) == 0) {
    if (sceClibStrncmp(name, "custom_text", 11) == 0) {
      if (string != NULL) {
        load_config_user();
        sceClibMemset(string, 0, 18);
        sceClibStrncpy(string, config.custom_text, length);
      }
    }
	save_config_user();
    return 0;
  }
  return TAI_CONTINUE(int, g_sceRegMgrGetKeyStr_SceSystemSettingsCore_hook, category, name, string, length);
}

static tai_hook_ref_t g_sceRegMgrSetKeyStr_SceSystemSettingsCore_hook;
static int sceRegMgrSetKeyStr_SceSystemSettingsCore_patched(const char *category, const char *name, const char *string, int length) {
  if (sceClibStrncmp(category, "/CONFIG/MACSPOOF", 16) == 0) {
    if (sceClibStrncmp(name, "custom_text", 11) == 0) {
      if (string != NULL) {
        sceClibMemset(config.custom_text, 0, 18);
        sceClibStrncpy(config.custom_text, string, length);
      }
    }
    save_config_user();
    return 0;
  }
  return TAI_CONTINUE(int, g_sceRegMgrSetKeyStr_SceSystemSettingsCore_hook, category, name, string, length);
}

static tai_hook_ref_t g_scePafToplevelGetText_SceSystemSettingsCore_hook;
static wchar_t *scePafToplevelGetText_SceSystemSettingsCore_patched(void *arg, char **msg) {
  language_container_t *language_container;
  int language = -1;
  sceRegMgrGetKeyInt("/CONFIG/SYSTEM", "language", &language);
  switch (language) {
    case SCE_SYSTEM_PARAM_LANG_JAPANESE:      language_container = &language_japanese;      break;
    case SCE_SYSTEM_PARAM_LANG_ENGLISH_US:    language_container = &language_english_us;    break;
    case SCE_SYSTEM_PARAM_LANG_FRENCH:        language_container = &language_french;        break;
    case SCE_SYSTEM_PARAM_LANG_SPANISH:       language_container = &language_spanish;       break;
    case SCE_SYSTEM_PARAM_LANG_GERMAN:        language_container = &language_german;        break;
    case SCE_SYSTEM_PARAM_LANG_ITALIAN:       language_container = &language_italian;       break;
    case SCE_SYSTEM_PARAM_LANG_DUTCH:         language_container = &language_dutch;         break;
    case SCE_SYSTEM_PARAM_LANG_PORTUGUESE_PT: language_container = &language_portuguese_pt; break;
    case SCE_SYSTEM_PARAM_LANG_RUSSIAN:       language_container = &language_russian;       break;
    case SCE_SYSTEM_PARAM_LANG_KOREAN:        language_container = &language_korean;        break;
    case SCE_SYSTEM_PARAM_LANG_CHINESE_T:     language_container = &language_chinese_t;     break;
    case SCE_SYSTEM_PARAM_LANG_CHINESE_S:     language_container = &language_chinese_s;     break;
    case SCE_SYSTEM_PARAM_LANG_FINNISH:       language_container = &language_finnish;       break;
    case SCE_SYSTEM_PARAM_LANG_SWEDISH:       language_container = &language_swedish;       break;
    case SCE_SYSTEM_PARAM_LANG_DANISH:        language_container = &language_danish;        break;
    case SCE_SYSTEM_PARAM_LANG_NORWEGIAN:     language_container = &language_norwegian;     break;
    case SCE_SYSTEM_PARAM_LANG_POLISH:        language_container = &language_polish;        break;
    case SCE_SYSTEM_PARAM_LANG_PORTUGUESE_BR: language_container = &language_portuguese_br; break;
    case SCE_SYSTEM_PARAM_LANG_ENGLISH_GB:    language_container = &language_english_gb;    break;
    case SCE_SYSTEM_PARAM_LANG_TURKISH:       language_container = &language_turkish;       break;
    default:                                  language_container = &language_english_us;    break;
  }
  if (msg && sceClibStrncmp(*msg, "msg_", 4) == 0) {
    #define LANGUAGE_ENTRY(name) \
      else if (sceClibStrncmp(*msg, #name, sizeof(#name)) == 0) { \
        return language_container->name; \
      }
    if (0) {}
    LANGUAGE_ENTRY(msg_macspoofer)
	LANGUAGE_ENTRY(msg_enable_macspoofing)
	LANGUAGE_ENTRY(msg_styleformat)
	LANGUAGE_ENTRY(msg_styleformat_0)
	LANGUAGE_ENTRY(msg_styleformat_1)
	LANGUAGE_ENTRY(msg_styleformat_2)
	LANGUAGE_ENTRY(msg_styleformat_3)
	LANGUAGE_ENTRY(msg_styleformat_4)
	LANGUAGE_ENTRY(msg_enable_customtext)
	LANGUAGE_ENTRY(msg_show_usecustomtext)
	LANGUAGE_ENTRY(msg_enter_customtext)
    LANGUAGE_ENTRY(msg_custom_text)
    #undef LANGUAGE_ENTRY
  }
  return TAI_CONTINUE(wchar_t *, g_scePafToplevelGetText_SceSystemSettingsCore_hook, arg, msg);
}

typedef struct {
  int size;
  const char *name;
  int type;
  int unk;
} SceRegMgrKeysInfo;

static tai_hook_ref_t g_sceRegMgrGetKeysInfo_SceSystemSettingsCore_hook;
static int sceRegMgrGetKeysInfo_SceSystemSettingsCore_patched(const char *category, SceRegMgrKeysInfo *info, int unk) {
  if (sceClibStrncmp(category, "/CONFIG/MACSPOOF", 16) == 0) {
    if (info) {
      if (sceClibStrncmp(info->name, "custom_text", 11) == 0) {
        info->type = 0x00030001; // type string
      } else {
        info->type = 0x00040000; // type integer
      }
    }
    return 0;
  }
  return TAI_CONTINUE(int, g_sceRegMgrGetKeysInfo_SceSystemSettingsCore_hook, category, info, unk);
}

static SceUID g_system_settings_core_modid = -1;
static tai_hook_ref_t g_sceKernelLoadStartModule_SceSettings_hook;
static SceUID sceKernelLoadStartModule_SceSettings_patched(char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status) {
  SceUID ret = TAI_CONTINUE(SceUID, g_sceKernelLoadStartModule_SceSettings_hook, path, args, argp, flags, option, status);
  if (ret >= 0 && sceClibStrncmp(path, "vs0:app/NPXS10015/system_settings_core.suprx", 44) == 0) {
    g_system_settings_core_modid = ret;										
    g_hooks[2] = taiHookFunctionImport(&g_sce_paf_private_snprintf_SceSettings_hook, 
                                      "SceSettings", 
                                      0xA7D28DAE, // ScePafStdc
                                      0x4E0D907E, 
                                      sce_paf_private_snprintf_SceSettings_patched);
									  
	g_hooks[3] = taiHookFunctionImport(&g_scePafMiscLoadXmlLayout_SceSettings_hook, 
                                      "SceSettings", 
                                      0x3D643CE8, // ScePafMisc
                                      0x19FE55A8, 
                                      scePafMiscLoadXmlLayout_SceSettings_patched);	
										
	g_hooks[4] = taiHookFunctionImport(&g_sceRegMgrGetKeyInt_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0xC436F916, // SceRegMgr
                                        0x16DDF3DC, 
                                        sceRegMgrGetKeyInt_SceSystemSettingsCore_patched);
    g_hooks[5] = taiHookFunctionImport(&g_sceRegMgrSetKeyInt_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0xC436F916, // SceRegMgr
                                        0xD72EA399, 
                                        sceRegMgrSetKeyInt_SceSystemSettingsCore_patched);
    g_hooks[6] = taiHookFunctionImport(&g_sceRegMgrGetKeyStr_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0xC436F916, // SceRegMgr
                                        0xE188382F, 
                                        sceRegMgrGetKeyStr_SceSystemSettingsCore_patched);
    g_hooks[7] = taiHookFunctionImport(&g_sceRegMgrSetKeyStr_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0xC436F916, // SceRegMgr
                                        0x41D320C5, 
                                        sceRegMgrSetKeyStr_SceSystemSettingsCore_patched);
    g_hooks[8] = taiHookFunctionImport(&g_sceRegMgrGetKeysInfo_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0xC436F916, // SceRegMgr
                                        0x58421DD1, 
                                        sceRegMgrGetKeysInfo_SceSystemSettingsCore_patched);
	g_hooks[9] = taiHookFunctionImport(&g_scePafToplevelGetText_SceSystemSettingsCore_hook, 
                                        "SceSystemSettingsCore", 
                                        0x4D9A9DD0, // ScePafToplevel
                                        0x19CEFDA7, 
                                        scePafToplevelGetText_SceSystemSettingsCore_patched);
  }
  return ret;
}

static tai_hook_ref_t g_sceKernelStopUnloadModule_SceSettings_hook;
static int sceKernelStopUnloadModule_SceSettings_patched(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status) {
  if (modid == g_system_settings_core_modid) {
    g_system_settings_core_modid = -1;
    if (g_hooks[2] >= 0) taiHookRelease(g_hooks[2], g_sce_paf_private_snprintf_SceSettings_hook);
	if (g_hooks[3] >= 0) taiHookRelease(g_hooks[3], g_scePafMiscLoadXmlLayout_SceSettings_hook);
	if (g_hooks[4] >= 0) taiHookRelease(g_hooks[4], g_sceRegMgrGetKeyInt_SceSystemSettingsCore_hook);
    if (g_hooks[5] >= 0) taiHookRelease(g_hooks[5], g_sceRegMgrSetKeyInt_SceSystemSettingsCore_hook);
    if (g_hooks[6] >= 0) taiHookRelease(g_hooks[6], g_sceRegMgrGetKeyStr_SceSystemSettingsCore_hook);
    if (g_hooks[7] >= 0) taiHookRelease(g_hooks[7], g_sceRegMgrSetKeyStr_SceSystemSettingsCore_hook);
    if (g_hooks[8] >= 0) taiHookRelease(g_hooks[8], g_sceRegMgrGetKeysInfo_SceSystemSettingsCore_hook);
	if (g_hooks[9] >= 0) taiHookRelease(g_hooks[9], g_scePafToplevelGetText_SceSystemSettingsCore_hook);
  }
  return TAI_CONTINUE(int, g_sceKernelStopUnloadModule_SceSettings_hook, modid, args, argp, flags, option, status);
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {
  load_config_user();
  g_hooks[0] = taiHookFunctionImport(&g_sceKernelLoadStartModule_SceSettings_hook, 
                                      "SceSettings", 
                                      0xCAE9ACE6, // SceLibKernel
                                      0x2DCC4AFA, 
                                      sceKernelLoadStartModule_SceSettings_patched);
  g_hooks[1] = taiHookFunctionImport(&g_sceKernelStopUnloadModule_SceSettings_hook, 
                                      "SceSettings", 
                                      0xCAE9ACE6, // SceLibKernel
                                      0x2415F8A4, 
                                      sceKernelStopUnloadModule_SceSettings_patched);
  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
  if (g_hooks[0] >= 0) taiHookRelease(g_hooks[0], g_sceKernelLoadStartModule_SceSettings_hook);
  if (g_hooks[1] >= 0) taiHookRelease(g_hooks[1], g_sceKernelStopUnloadModule_SceSettings_hook);
  return SCE_KERNEL_STOP_SUCCESS;
}
