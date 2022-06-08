#include <dxgi1_5.h>
#include <d3d11.h>
#include <stdio.h>
#include <assert.h>
#include <process.h>



class screencut
{
private:
    ID3D11Device           *m_hDevice = nullptr;
    ID3D11DeviceContext    *m_hContext = nullptr;
    IDXGIOutputDuplication *m_hDeskDupl = nullptr;
    int iWidth  = 0;
    int iHeight = 0;

    BOOL Init();
    void Finit();
public:

    BOOL AttatchToThread(VOID);
    BOOL QueryFrame(const char *fileName, void *pImgData, INT &nImgSize);
    void rotateImg(unsigned char *pImgData);
    void saveBmpFile(const char *fileName, unsigned char *pImgData, int imgLength);
    unsigned char * capture() ;//返回一个 CV_8UC4 的图像指针 请别忘了delete

    screencut(/* args */);
    ~screencut();
};

