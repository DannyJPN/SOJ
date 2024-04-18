#include <Moje.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     Moje
 * Method:    nic
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_Moje_celecislo(JNIEnv *, jclass, jint i)
{ return i; }

JNIEXPORT jint JNICALL Java_Moje_pole(JNIEnv *e, jclass, jintArray p)
{
  return 0;
}

#ifdef __cplusplus
}
#endif

