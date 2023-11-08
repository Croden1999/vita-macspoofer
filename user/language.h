#ifndef LANGUAGE_HEADER
#define LANGUAGE_HEADER

typedef struct{
	wchar_t *msg_macspoofer;
	wchar_t *msg_enable_macspoofing;
	wchar_t *msg_styleformat;
	wchar_t *msg_styleformat_0;
	wchar_t *msg_styleformat_1;
	wchar_t *msg_styleformat_2;
	wchar_t *msg_styleformat_3;
	wchar_t *msg_styleformat_4;
	wchar_t *msg_enable_customtext;
	wchar_t *msg_show_usecustomtext;
	wchar_t *msg_enter_customtext;
	wchar_t *msg_custom_text;
} language_container_t;

language_container_t language_japanese = {  
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_english_us = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_french = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_spanish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_german = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_italian = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_dutch = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_portuguese_pt = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_russian = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_korean = {
 	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_chinese_t = {
	L"MAC地址僞裝",
	L"啟用MAC僞裝",
	L"樣式格式",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"使用自訂文本",
	L"啟用顯示您所選擇的自訂文本",
	L"輸入自訂文本",
	L"最多可以使用18個字符",
};

language_container_t language_chinese_s = {
	L"MAC地址伪装",
	L"启用MAC伪装",
	L"样式格式",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"使用自定义文本",
	L"启用显示您所选择的自定义文本",
	L"输入自定义文本",
	L"最多可以使用18个字符",
};

language_container_t language_finnish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_swedish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_danish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_norwegian = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_polish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_portuguese_br = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_english_gb = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

language_container_t language_turkish = {
	L"MAC Address Spoof",
	L"Enable MAC Spoofing",
	L"Style Format",
	L"00:00:00:00:00:00",
	L"XX:XX:XX:XX:XX:XX",
	L"??:??:??:??:??:??",
	L"##:##:##:##:##:##",
	L"--:--:--:--:--:--",
	L"Use Custom Text",
	L"Enable to show a custom text of your choice instead",
	L"Enter Custom Text",
	L"You can use up to 18 characters",
};

#endif // LANGUAGE_HEADER
