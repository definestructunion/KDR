#ifndef _KDR_UTIL_HPP
#define _KDR_UTIL_HPP

#define ARRAYMEMORYSIZE(ARRAY , TYPE) sizeof(ARRAY) * sizeof(TYPE)
#define ASSERT(x) if(!(x)) __debugbreak();

#define GLASSERT(x) gl_clear_errors();\
				   x;\
				   ASSERT(gl_log_call(#x, __FILE__, __LINE__))

#define VAL_TO_UNSIGNED(val) ((val < 0) ? val *= -1 : val)
#define LOG(x) std::cout << x << std::endl;

#define SOUND_VEC_NAMES SOUND_NAMES
#define TEXTURE_VEC_NAMES TEXTURE_NAMES

//#define SOUND_VEC_NAMES enum NAME SOUND_NAMES;
//#define TEXTURE_VEC_NAMES enum NAME TEXTURE_NAMES

void gl_clear_errors();
void gl_check_errors();
bool gl_log_call(const char* function, const char* file, int line);

#endif //