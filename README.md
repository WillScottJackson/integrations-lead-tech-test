1. Code Review and Changes 
- My major criticism with this project is that it is built using MFC. This wouldn't be my first choice 
of framework, I think using a more modern framework such as Qt would be far more beneficial, as it 
is cross platform, continuously supported and uses modern C++ features.
- I replaced instances of #define with constexpr for a few reasons, the first is type safety, the second is having the constant defined at compile time, the third is that I could encapsulate the constants in a namespace or as part of an enum so I can carefully manage their scope
- The constants MIN_WINDOW_WIDTH and MIN_WINDOW_HEIGHT appeared to be unused, but I added them to the CreateWindowW function
- The global variables should be encapsulated into another class or namespace so their scope can be carefully managed and they don't inadvertently cause problems. Possibly as a Singleton 
- For the sake of type safety, I replaced C-style casts with static casts where appropriate. 
- There are a few "magic numbers" in the code which don't have any explanation, for example GetMessage() in wWinMain. These should either be replaced with the appropriate MFC constants, or constants should be defined to make their meaning clear 
- Is it possible for MSG msg to be remain unitialized in wWinMain() should the first call of GetMessage() fail and not write to msg? If so it could be possible that the return code could be uninitialized
- There were a few more "magic numbers" in WndProc for the return codes, I think 0 was in appropriate based on the context, so I replaced them with what I think are the appropriate codes. 
- For the sake of readability and tidiness I moved some of the forward declarations and constant definitions to the .h file 
- There's a style inconsistency in WndProc, in CASE WM_PAINT, some code is encapsulated within braces {}
, this isn't needed as the variables declared within the case, are within a new scope anyway and will be destroyed when you leave the scope of the case WM_PAINT. However, if it is being used for scope limitation, preventing fallthrough etc. it's best to use it in every case 