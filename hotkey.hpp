#define HOT_KEY_IMP_
#include <iostream>
#include <functional>
#include <bitset>
#ifdef HOT_KEY_IMP_
class __declspec(dllexport) HotKey {
#else
class __declspec(dllimport) HotKey {
#endif // HOT_KEY_IMP_

private:
	DWORD tid;
	HANDLE t;

public:
	HotKey();
	~HotKey();
	
	void Register(UINT mod, UINT key, std::function<void(void)> func);
	void Unregister(UINT mod, UINT key);
};
std::string getmodstr(UINT mod);
int getmodbin(UINT mod);
bool stop = false;

#define WM_ADD_HOTKEY (WM_USER + 0x0001)
#define WM_DEL_HOTKEY (WM_USER + 0x0002)
#define WM_END (WM_USER + 0x0003)

struct HotKeyInfo {
	UINT fsModifiers;
	UINT vk;
	std::function<void(void)> func;
	bool active;
	
};

DWORD WINAPI hotkeythreadfunc(LPVOID lpParameter) {
	std::vector<HotKeyInfo> hotkeys;
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			UINT vk = msg.wParam;
			UINT mod = msg.lParam;
			std::cout << "WM_HOTKEY received :"  <<getmodstr(mod) << (char)vk<< std::endl;
			for (auto i=0;i<hotkeys.size();i++) {
				if ((getmodbin(hotkeys[i].fsModifiers) == getmodbin(mod)) && ((i+1) == vk)) {
					try {
						hotkeys[i].func();
					}
					catch (std::exception e) {
						std::cerr << e.what() << std::endl;
					}
				}
			}
		}
		else if (msg.message == WM_ADD_HOTKEY) {
			HotKeyInfo* info_p = (HotKeyInfo*)msg.wParam;
			HotKeyInfo info = *info_p;
			delete info_p;

			bool regtrue=RegisterHotKey(NULL, hotkeys.size() + 1, info.fsModifiers, info.vk);
			if (regtrue==0){
				printf("register hotkey fail\n");
			}
			else{
				printf("register hotkey succeed\n");
			}
			info.active = true;
			hotkeys.push_back(info);

		}
		else if (msg.message == WM_DEL_HOTKEY) {
			HotKeyInfo* info_p = (HotKeyInfo*)msg.wParam;
			HotKeyInfo info = *info_p;
			delete info_p;

			for (int i = 0; i < hotkeys.size(); i++) {
				HotKeyInfo hotkey = hotkeys[i];
				if (hotkey.fsModifiers == info.fsModifiers && hotkey.vk == info.vk) {
					UnregisterHotKey(NULL, i + 1);
					hotkey.active = false;
				}
			}
		}
		else if (msg.message == WM_END) {
			for (int i = 0; i < hotkeys.size(); i++) {
				HotKeyInfo hotkey = hotkeys[i];
				if (hotkey.active) {
					UnregisterHotKey(NULL, i);
					hotkey.active = false;
				}
			}
			break; // end message loop
		}
	}
	return 0;
}

HotKey::HotKey() {
	t = CreateThread(NULL, 0, hotkeythreadfunc, NULL, 0, &tid);
	printf("tid=%d\n",tid);
}

void HotKey::Register(UINT mod, UINT key, std::function<void(void)> func) {
	HotKeyInfo* info = new HotKeyInfo();
	info->fsModifiers = mod;
	info->vk = key;
	info->func = func;
	printf("regkey=%c\n",key);
	PostThreadMessage(tid, WM_ADD_HOTKEY, (WPARAM)info, 0);
}

void HotKey::Unregister(UINT mod, UINT key) {
	HotKeyInfo* info = new HotKeyInfo();
	info->fsModifiers = mod;
	info->vk = key;
	PostThreadMessage(tid, WM_DEL_HOTKEY, (WPARAM)info, 0);
}

HotKey::~HotKey() {
	PostThreadMessage(tid, WM_END, 0, 0);
	while (WaitForSingleObject(t, 100) == WAIT_TIMEOUT) {
		Sleep(50);
	}
}
std::string getmodstr(UINT mod){
	std::string modstr;
	if ((mod&MOD_ALT)==MOD_ALT){
		modstr.append("ALT ");
	}
	if ((mod&MOD_CONTROL)==MOD_CONTROL){
		modstr.append("CONTROL ");
	}
	if ((mod&MOD_NOREPEAT)==MOD_NOREPEAT){
		modstr.append("NOREPEAT ");
	}
	if ((mod&MOD_SHIFT)==MOD_SHIFT){
		modstr.append("SHIFT ");
	}
	if ((mod&MOD_WIN)==MOD_WIN){
		modstr.append("WIN ");
	}
	return modstr;
}
int getmodbin(UINT mod){
	int b=0;
	if ((mod&MOD_ALT)==MOD_ALT){
		b|=MOD_ALT;
	}
	if ((mod&MOD_CONTROL)==MOD_CONTROL){
		b|=MOD_CONTROL;
	}
	if ((mod&MOD_SHIFT)==MOD_SHIFT){
		b|=MOD_SHIFT;
	}
	if ((mod&MOD_WIN)==MOD_WIN){
		b|=MOD_WIN;
	}
	return b;
}