
class keyboard
{
private:
    std::default_random_engine RandEngine;
    std::uniform_int_distribution<unsigned> RandValue10_30=std::uniform_int_distribution<unsigned> (10,30);
public:
    keyboard();
    void key(char key,char scan=0);
    void keydown(char key,char scan=0);
    void keyup(char key,char scan=0);
    void alt_(char key,char scan=0);
    void ctrl_(char key,char scan=0);
    void shift_(char key,char scan=0);
    ~keyboard();
};

void keyboard::key(char key,char scan){
    keybd_event(key, scan, 0, 0);
    Sleep((DWORD)RandValue10_30(RandEngine));
    keybd_event(key, scan, KEYEVENTF_KEYUP, 0);
}
void keyboard::keydown(char key,char scan){
    keybd_event(key, scan,0,0);
}
void keyboard::keyup(char key,char scan){
    keybd_event(key, scan,KEYEVENTF_KEYUP,0);
}
void keyboard::alt_(char key,char scan){
    keydown(VK_MENU,0x38);
    keydown(key,scan);
    Sleep((DWORD)RandValue10_30(RandEngine));
    keyup(VK_MENU,0xB8);
    keyup(key,scan);
}
void keyboard::shift_(char key,char scan){
    keydown(VK_LSHIFT,0x2A);
    keydown(key,scan);
    Sleep((DWORD)RandValue10_30(RandEngine));
    keyup(VK_LSHIFT,0xAA);
    keyup(key,scan);
}
void keyboard::ctrl_(char key,char scan){
    keydown(VK_MENU,0x1D);
    keydown(key,scan);
    Sleep((DWORD)RandValue10_30(RandEngine));
    keyup(VK_LSHIFT,0x9D);
    keyup(key,scan);
}
keyboard::keyboard()
{
    
}

keyboard::~keyboard()
{
}
