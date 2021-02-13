#include "PowerTipApp.h"

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifdef NDEBUG
int WINAPI
WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#else
int _tmain(int __argc, char **__argv)
{
#endif
#else
int main(int __argc, char **__argv)
{
#endif

#if NDEBUG
    return PowerTipApp().run(__argc, __argv);
#else
    return PowerTipApp().run(0, nullptr);
#endif
}