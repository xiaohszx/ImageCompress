
#include "ImageCompress.h"

// ��ָ���ļ����µ�ͼƬ���н���ѹ��/��ѹ��.
int main(int argc, const char **argv) {

	const char *dir = argc > 1 ? argv[1] : "./face";

	bool b = Compress(dir, 25);

	return 0;
}
