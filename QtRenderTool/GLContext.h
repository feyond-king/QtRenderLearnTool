#pragma once

#include <windows.h>
#include <GL/glew.h>

class GLContext
{
protected:
    int         _format;
    // ���ھ��
    HWND        _hWnd;
    // �����豸������
    HDC         _hDC;
    // OpenGL������
    HGLRC       _hRC;
public:
    GLContext();

    ~GLContext();

    /**
    *   ��ʼ��GL
    */
    bool    setup(HWND hWnd, HDC hDC);

    /**
    *   ����OpenGL
    */
    void    shutdown();

    /**
    *   ����������
    */
    void    swapBuffer();

};
