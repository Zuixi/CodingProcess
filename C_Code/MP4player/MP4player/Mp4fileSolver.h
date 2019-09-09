#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>

using namespace std;
//filetype 表明文件类型
typedef struct ftyp_box {
	string major_brand;
	short minor_version;
	vector<string> compatible_brands;
}file_type;
//movie header，文件总体信息
typedef struct mvhd_box {
	int time_scale;
	int32_t duration;
	int32_t movie_time;
	float rate;
	float volume;
}movie_header;


//track的头文件，包含时长，宽高等
typedef struct tkhd_box {
	short flags;
	int32_t duration;
	float volume;
	double width;
	double height;
}track_header;

//media容器头
typedef struct mdhd_box {
	int32_t time_scale;
	int32_t duration;
	int32_t language;
}media_header;


struct stts_sample {
	int samplecount;
	int sampledelta;
};


//时间戳和sample序号的映射表
typedef struct stts_box {
	int size;
	vector<stts_sample* > samples;
}time_to_sample;

struct stsc_entry
{
	int firstchunk;
	int samples_per_chunk;
	int sample_description_index;
};

//sample和chunk的映射表
typedef struct stsc_box {
	int size;
	vector<stsc_entry*> entries;
}sample_to_chunk;
//sample大小
typedef struct stsz_box {
	int entry_size;
	int size;
	vector<int> sample_sizes;
}sample_size;

//另一个samplesize存储法
typedef struct stz2_box {

}sample_size_2;

//可随机访问的sample列表
typedef struct stss_box {
	int size;
	vector<int> sample_number;
}sync_sample_table;
//chunk offset 每个chunk的偏移大小
typedef struct stco_box {
	int size;
	vector<int> chunk_offsets;
}chunk_offset;


struct avCC_box {
	short Configuration_version;
	short AVC_profile_indication;
	short profile_compatible;
	short AVC_level_indication;
};
struct avc1_box {

	avCC_box avcc;
	short data_reference_index;
	short width;
	short height;
	double horizontal_resolution;
	double vertical_resolution;
	short frame_count;
	int depth;
};

typedef struct co64_box {

}chunk_offset_64;
//具体媒体数据
typedef struct mdat_box {
	FILE* media_data_head;
}file_metadata;
struct stsd_box {
	int entrycount;
	avc1_box avc1;
};
struct ctts_sample
{
	int sample_count;
	int sample_offset;
};

struct ctts_box {
	int size;
	vector<ctts_sample*> samples;
};
//sample table box 存放时间 偏移关系
typedef struct stbl_box {
	stsc_box stsc;
	stss_box stss;
	stsz_box stsz;
	stco_box stco;
	stsd_box stsd;
	stts_box stts;
	ctts_box ctts;
	


	co64_box co64;
}sample_table_box;

//媒体文件数据
typedef struct minf_box {
	stbl_box stbl;
}media_information_contianer;


//media信息容器
typedef struct mdia_box {
	mdhd_box mdhd;
	minf_box minf;
}track_media_information_container;
//trak存放音频或视频流的容器
typedef struct trak_box {
	tkhd_box tkhd;
	mdia_box mdia;
}track;
//metada container，存放媒体信息
typedef struct  moov_box {
	mvhd_box mvhd;
	trak_box* video;
	trak_box* audio;
}metadata_container;



class MP4File {
private:
	fstream* mp4f;

	FILE* mp4fp;
	FILE* mdatafp;
	ftyp_box filetype;
	moov_box metadata_contianer;



	//数字反转
	int number_reverse(int number);
	short number_reverse(short number);
	void fytp_read(int size);
	void moov_read(int size);
	void skip_read(int size);
	void mdata_read();
	void mvhd_read(int size);
	void trak_read(int size);
	void tkhd_read(int size, trak_box* track1);
	void mdia_read(int size, trak_box* track1);
	void mdhd_read(int size, trak_box* track1);
	void hdlr_read(int size, trak_box* track1);
	void minf_read(int size, trak_box* track1);
	void vmhd_read(int size, trak_box* track1);
	void stbl_read(int size, trak_box* track1);
	void stsd_read(int size, trak_box* track1);
	void avc1_read(int size, trak_box* track1);
	void avCC_read(int size, trak_box* track1);
	void stss_read(int size, trak_box* track1);
	void stts_read(int size, trak_box* track1);
	void ctts_read(int size, trak_box* track1);
	void stsc_read(int size, trak_box* track1);
	void stsz_read(int size, trak_box* track1);
	void stco_read(int size, trak_box* track1);

	bool open_file();
	bool open_file(string path);

	int num_read();
	short num_read(int a);
	double num_read(float a);
	
public:
	bool IniMp4File(string path);
	void ShowMp4data();

	bool OpenFile(string path);
};

