
#include "ImageCompress.h"

// ��ָ���ļ����µ�ͼƬ���н���ѹ��/��ѹ��.
int main(int argc, const char **argv) {

	const char *dir = argc > 1 ? argv[1] : "./face";

	bool b = Compress(dir, 25);

	bool c = UnCompress(dir, 25);

	system("PAUSE");

	return 0;
}
