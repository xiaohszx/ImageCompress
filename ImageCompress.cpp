#include <io.h>
#include <vector>
#include "zlib\zlib.h"
#include "ImageCompress.h"


// ��ȡָ��Ŀ¼�µ�ͼƬ.
std::vector<std::string> ListImages(const std::string &dir)
{
	std::vector<std::string> ret;
	//�ļ����
	intptr_t hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	std::string p;
	try
	{
		if ((hFile = _findfirst(p.assign(dir).append("\\*.jpg").c_str(), &fileinfo)) != -1)
		{
			do {
				std::string child = dir + "\\" + fileinfo.name;
				ret.push_back(child);
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	catch (std::exception e) { if (hFile) _findclose(hFile); }

	return ret;
}

// ����ͼƬ�ļ�.
int save(const std::string &path, const cv::Mat &ref, const cv::Mat &m) {
	cv::Mat n, t = m > ref;
	cv::absdiff(m, ref, n);
	std::string new_path = path;
	FILE *f = fopen(new_path.c_str(), "wb");
	if (f)
	{
		uchar *buffer = new uchar[n.rows * n.step[0]];
		uLongf dst = n.rows * n.step[0], src = t.rows * t.step[0];
		// �С�������+����
		fwrite(&n.rows, sizeof(n.rows), 1, f);
		fwrite(&n.step[0], sizeof(n.cols), 1, f);
		int s = compress(buffer, &dst, t.data, t.rows * t.step[0]);
		fwrite(buffer, 1, dst, f);
		s = compress(buffer, &dst, n.data, n.rows * n.step[0]);
		fwrite(buffer, 1, dst, f);
		delete[] buffer;
		fclose(f);
	}
	return 1;
}

// ��ͼƬĿ¼����ѹ��.
bool Compress(const char * dir, int step)
{
	std::vector<std::string> images = ListImages(dir);
	if (images.size() == 0)
	{
		return false;
	}
	cv::Mat ref = cv::imread(images.at(0));
	for (int i=1, c = 0; i < images.size(); ++i)
	{
		cv::Mat m = cv::imread(images.at(i));
		if (m.rows != ref.rows || m.cols != ref.cols)
			continue;
		if (++c <= step){
			save(images.at(i).c_str(), ref, m);
		}else{
			c = 0;
			ref = m;
		}
	}
	
	return false;
}
