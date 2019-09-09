#include "Mp4fileSolver.h"




//����ת��
int MP4File::number_reverse(int number)
{
	
	uint32_t hx = 0xFF000000;
	uint32_t result = 0;
	for (int i = 3; i >= 0; i--)
	{
		int k = number & 0xFF;
		if (k)
		{
			int a = k << (8 * i);
			result += a;
		}
		hx = hx >> 8;
		number = number >> 8;
	}


	return result;
	
}

short MP4File::number_reverse(short number)
{
	uint16_t hx = 0xFF00;
	uint16_t result = 0;
	for (int i = 1; i >= 0; i--)
	{
		int k = number & 0xFF;
		if (k)
		{
			int a = k << (8 * i);
			result += a;
		}
		hx = hx >> 8;
		number = number >> 8;
	}


	return result;
}

void MP4File::fytp_read(int size)
{
	//��filetype��ֵ
	char mbrand[5];
	char cbrand[5];
	int mversion;
	//mbrand
	//mp4f->read(mbrand, sizeof(mbrand)-1);
	fread(&mbrand, sizeof(char), 4, mp4fp);
	mbrand[4] = '\0';
	filetype.major_brand = mbrand;
	//mversion
	mversion = num_read();
	filetype.minor_version = mversion;
	//cbrand
	int cbrandnum = (size / 4) - 4;
	for (cbrandnum; cbrandnum > 0; cbrandnum--)
	{
		//mp4f->read(cbrand, sizeof(cbrand)-1);
		fread(&cbrand, sizeof(char), 4, mp4fp);
		cbrand[4] = '\0';
		string s = cbrand;
		filetype.compatible_brands.push_back(s);
	}
}

void MP4File::moov_read(int size)
{
	size -= 8;
	char box_name[5];
	box_name[4] = '\0';
	//�Զ��� ��mvhd��track ����������
	//��β���ߵ�����������box���˳���ά��һ��size������Ϊ0ʱ���꣬�˳�
	while (size > 0)
	{
		int sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);
		if (!strcmp(box_name, "trak"))
		{
			size -= sbox_size;
			//��ȡtrack
			trak_read(sbox_size);
		}
		else if (!strcmp(box_name, "mvhd"))
		{
			size -= sbox_size;
			//��ȡmvhd
			mvhd_read(sbox_size);
		}
		else {
			//������ǰbox��С�Ŀռ�
			size -= sbox_size;
			skip_read(sbox_size);
		}



	}

}

void MP4File::skip_read(int size)
{
	//��ȡ��С �������Ƭ��
	size -= 8;
	//mp4f->seekg(size, ios::cur);
	fseek(mp4fp, size, SEEK_CUR);
}

void MP4File::mdata_read()
{
	//ɨһ���ļ���ֱ���ﵽmdata����

}

void MP4File::mvhd_read(int size)
{
	
	//mp4f->seekg(12, ios::cur);
	fseek(mp4fp, 12, SEEK_CUR);
	//time_scale
	metadata_contianer.mvhd.time_scale = num_read();
	//duration
	metadata_contianer.mvhd.duration = num_read();
	//rate
	short rate;
	//mp4f->read((char*)(&rate), sizeof(rate));
	fread(&rate, sizeof(short), 1, mp4fp);
	rate = number_reverse(rate);

	//��������
	metadata_contianer.mvhd.rate += rate;
	//mp4f->read((char*)(&rate), sizeof(rate));
	fread(&rate, sizeof(short), 1, mp4fp);
	rate = number_reverse(rate);
	//С������
	float r1 = rate;
	float l = pow(10, rate / 10 + 1);
	metadata_contianer.mvhd.rate += (l * r1);

	//volume,ֱ������1.0 ��ʱ��ʱ���ٸ�
	//mp4f->read((char*)(&rate), sizeof(rate));
	fread(&rate, sizeof(short), 1, mp4fp);
	metadata_contianer.mvhd.volume = 1.0f;
	//matrix,�����Ҫ�ٶ�����ʱֱ������
	//mp4f->seekg(74, ios::cur);
	fseek(mp4fp, 74, SEEK_CUR);

}

void MP4File::trak_read(int size)
{
	//Ҫά��size��ֱ��size����
	size -= 8;
	char box_name[5];
	box_name[4] = '\0';
	int sbox_size;
	trak_box* track1 = new trak_box();
	//���ϲ�ͬ�����Զ���
	while (size > 0)
	{
		sbox_size=num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);

		if (!strcmp(box_name, "tkhd"))
		{
			//��ȡtkhd
			size -= sbox_size;
			tkhd_read(sbox_size, track1);					
		}
		else if (!strcmp(box_name, "mdia"))
		{
			size -= sbox_size;
			mdia_read(sbox_size, track1);
		}
		else
		{
			//����û�õ�box
			size -= sbox_size;
			skip_read(sbox_size);
		}


	}
}

void MP4File::tkhd_read(int size, trak_box* track1)
{
	//�������õ�����
	//mp4f->seekg(20, ios::cur);
	fseek(mp4fp, 20, SEEK_CUR);
	//��ȡduration
	track1->tkhd.duration = num_read();
	//����12������λ
	//mp4f->seekg(12, ios::cur);
	fseek(mp4fp, 12, SEEK_CUR);


	//��ȡvolumeλ�������0�͹������Ǿͱ��1
	short volume;
	//mp4f->read((char*)(&volume), sizeof(volume));
	fread(&volume, sizeof(short), 1, mp4fp);
	if (volume != 0)
	{
		track1->tkhd.volume = 1.0f;
	}
	//����Ԥ��λ
	//mp4f->seekg(2, ios::cur);
	fseek(mp4fp, 2, SEEK_CUR);
	//������Ƶ�任���������Ҫ�Ժ�����
	//mp4f->seekg(36, ios::cur);
	fseek(mp4fp, 36, SEEK_CUR);

	//���
	track1->tkhd.width = num_read(1.0f);
	track1->tkhd.height = num_read(1.0f);
}

void MP4File::mdia_read(int size, trak_box* track1)
{
	//��trackһ�����Զ���
	int sbox_size;
	char box_name[5];
	box_name[4] = '\0';
	size -= 8;
	while (size > 0)
	{
		sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);
		if (!strcmp(box_name, "mdhd"))
		{
			//mdhd��ȡ
			size -= sbox_size;
			mdhd_read(sbox_size,track1);

		}
		else if (!strcmp(box_name, "hdlr"))
		{
			size -= sbox_size;
			hdlr_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "minf"))
		{
			size -= sbox_size;
			minf_read(sbox_size,track1);

		}
		else
		{
			size -= sbox_size;
			skip_read(sbox_size);
		}
	}



}

void MP4File::mdhd_read(int size, trak_box* track1)
{
	//��������ʱ���12��
	//mp4f->seekg(12, ios::cur);

	fseek(mp4fp, 12, SEEK_CUR);
	track1->mdia.mdhd.time_scale = num_read();
	track1->mdia.mdhd.duration = num_read();
	track1->mdia.mdhd.language = num_read((short)1);
	//mp4f->seekg(2, ios::cur);
	fseek(mp4fp, 2, SEEK_CUR);

}

void MP4File::hdlr_read(int size, trak_box* track1)
{
	//mp4f->seekg(8, ios::cur);
	fseek(mp4fp, 8, SEEK_CUR);
	//��ȡ��video����audio
	char type[5];
	type[4] = '\0';
	//mp4f->read(type, sizeof(type) - 1);
	fread(&type, sizeof(char), 4, mp4fp);

	if (!strcmp(type, "vide"))
	{
		metadata_contianer.video = track1;
	}
	else if (!strcmp(type, "soun"))
	{
		metadata_contianer.audio = track1;
	}
	//mp4f->seekg(size - 20, ios::cur);
	fseek(mp4fp, size-20, SEEK_CUR);

}

void MP4File::minf_read(int size, trak_box* track1)
{
	//�Զ���
	size -= 8;
	int sbox_size;
	char box_name[5];
	box_name[4] = '\0';

	while (size > 0)
	{
		sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);

		if (!strcmp(box_name, "vmhd"))
		{
			size -= sbox_size;
			vmhd_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stbl"))
		{
			size -= sbox_size;
			stbl_read(sbox_size, track1);

		}
		else
		{
			size -= sbox_size;
			skip_read(sbox_size);
		}


	}
}

void MP4File::vmhd_read(int size, trak_box* track1)
{
	//��ʱ����
	//mp4f->seekg(size - 8, ios::cur);
	fseek(mp4fp, size-8, SEEK_CUR);
}

void MP4File::stbl_read(int size, trak_box* track1)
{
	//�Զ��� �����Զ���
	size -= 8;
	int sbox_size;
	char box_name[5];
	box_name[4] = '\0';
	while (size > 0)
	{
		sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);

		if (!strcmp(box_name, "stsd"))
		{
			size -= sbox_size;
			stsd_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stss"))
		{
			size -= sbox_size;
			stss_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stts"))
		{
			size -= sbox_size;
			stts_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "ctts"))
		{
			size -= sbox_size;
			ctts_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stsc"))
		{
			size -= sbox_size;
			stsc_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stsz"))
		{
			size -= sbox_size;
			stsz_read(sbox_size, track1);
		}
		else if (!strcmp(box_name, "stco"))
		{
			size -= sbox_size;
			stco_read(sbox_size, track1);
		}
		else
		{
			size -= sbox_size;
			skip_read(sbox_size);
		}


	}
}

void MP4File::stsd_read(int size, trak_box* track1)
{
	size -= 16;
	//����4����Ч��
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	//����entrycount
	track1->mdia.minf.stbl.stsd.entrycount = num_read();
	int sbox_size;
	char box_name[5];
	box_name[4] = '\0';
	//�Զ���
	while (size > 0)
	{
		sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);

		if (!strcmp(box_name, "avc1"))
		{
			size -= sbox_size;
			avc1_read(sbox_size, track1);

		}
		else if (!strcmp(box_name, "mp4a"))
		{
			size -= sbox_size;
			skip_read(sbox_size);
		}
		else
		{
			size -= sbox_size;
			skip_read(sbox_size);
		}


	}
}

void MP4File::avc1_read(int size, trak_box* track1)
{
	size -= 86;
	int sbox_size;
	char box_name[5];
	box_name[4] = '\0';

	//avc1���ݶ�ȡ
	//��4����Ч��
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);

	//data reference
	track1->mdia.minf.stbl.stsd.avc1.data_reference_index = num_read();

	//��Ч������
	//mp4f->seekg(16, ios::cur);
	fseek(mp4fp, 16, SEEK_CUR);

	track1->mdia.minf.stbl.stsd.avc1.width = num_read(1);
	track1->mdia.minf.stbl.stsd.avc1.height = num_read(1);
	track1->mdia.minf.stbl.stsd.avc1.horizontal_resolution = num_read(1.0f);
	track1->mdia.minf.stbl.stsd.avc1.vertical_resolution = num_read(1.0f);
	//mp4f->seekg(36, ios::cur);
	fseek(mp4fp, 36, SEEK_CUR);
	track1->mdia.minf.stbl.stsd.avc1.depth = num_read();
	track1->mdia.minf.stbl.stsd.avc1.frame_count = 1;
	//mp4f->seekg(2, ios::cur);
	fseek(mp4fp, 2, SEEK_CUR);


	while (size > 0)
	{
		sbox_size = num_read();
		//mp4f->read(box_name, sizeof(box_name) - 1);
		fread(&box_name, sizeof(char), 4, mp4fp);

		if (!strcmp(box_name, "avcC"))
		{
			size -= sbox_size;
			avCC_read(sbox_size, track1);
		}
		else {
			size -= sbox_size;
			skip_read(sbox_size);
		}

	}


}

void MP4File::avCC_read(int size, trak_box* track1)
{
	//��ʱ��������
	skip_read(size);
}

void MP4File::stss_read(int size, trak_box* track1)
{
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int i = num_read();
	track1->mdia.minf.stbl.stss.size = i;
	for (i; i > 0; i--)
	{
		int sample_num = num_read();
		track1->mdia.minf.stbl.stss.sample_number.push_back(sample_num);
	}
}

void MP4File::stts_read(int size, trak_box* track1)
{
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int i = num_read();
	track1->mdia.minf.stbl.stss.size = i;
	stts_sample* sample;
	for (i; i > 0; i--)
	{
		sample = new stts_sample();
		sample->samplecount = num_read();
		sample->sampledelta = num_read();
		track1->mdia.minf.stbl.stts.samples.push_back(sample);
	}

}

void MP4File::ctts_read(int size, trak_box* track1)
{
	/*skip_read(size);*/
	//mp4f->seekg(3,ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int i;
	i=num_read();
	track1->mdia.minf.stbl.ctts.size = i;
	ctts_sample* sample;
	for (i; i > 0; i--)
	{
		sample = new ctts_sample();
		sample->sample_count = num_read();
		sample->sample_offset = num_read();
		track1->mdia.minf.stbl.ctts.samples.push_back(sample);
	}
}

void MP4File::stsc_read(int size, trak_box* track1)
{
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int i = num_read();
	stsc_entry* entry;
	track1->mdia.minf.stbl.stsc.size = i;
	for (i; i > 0; i--)
	{
		entry = new stsc_entry();
		entry->firstchunk = num_read();
		entry->samples_per_chunk = num_read();
		entry->sample_description_index = num_read();
		track1->mdia.minf.stbl.stsc.entries.push_back(entry);
	}
}

void MP4File::stsz_read(int size, trak_box* track1)
{
	/*skip_read(size);*/
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int i;
	track1->mdia.minf.stbl.stsz.entry_size = num_read(); 
	i = num_read();
	if (track1->mdia.minf.stbl.stsz.entry_size == 0)
	{
		int sample;
		for (i; i > 0; i--)
		{
			sample = num_read();
			track1->mdia.minf.stbl.stsz.sample_sizes.push_back(sample);
		}
	}

}

void MP4File::stco_read(int size, trak_box* track1)
{
	//mp4f->seekg(4, ios::cur);
	fseek(mp4fp, 4, SEEK_CUR);
	int chunk_offset;
	int i = num_read();
	track1->mdia.minf.stbl.stco.size = i;
	for (i; i > 0; i--)
	{
		//mp4f->read((char*)(&result), sizeof(result));
		chunk_offset = num_read();
		track1->mdia.minf.stbl.stco.chunk_offsets.push_back(chunk_offset);
	}
}



bool MP4File::open_file()
{
	if (mp4fp != NULL)
	{
		char box_type[5];
		box_type[4] = '\0';
		int size;
		//ѭ������ֱ�������ļ���β
		while (!feof(mp4fp))
		{


			size = num_read();
			if (size == -858993460)
				break;
			//mp4f->read(box_type, sizeof(box_type) - 1);	
			fread(box_type, sizeof(char), 4, mp4fp);
			if (!strcmp(box_type, "ftyp"))
				fytp_read(size);
			else if (!strcmp(box_type, "moov"))
				moov_read(size);
			else
				skip_read(size);
		}
		return true;

	}
	else
	{
		return false;
	}


}

bool MP4File::open_file(string path)
{
	//step1 ���ļ�������ļ�ͷ
	if (!OpenFile(path))
	{
		return false;
	}
	//��ȡ���֣���������ѡ����Ӧ�ĺ���
	char box_type[5];
	box_type[4] = '\0';
	int size;

	//ѭ������ֱ�������ļ���β
	while (!feof(mp4fp))
	{


		size = num_read();
		if (size == -858993460)
			break;
		//mp4f->read(box_type, sizeof(box_type) - 1);	
		fread(box_type, sizeof(char), 4, mp4fp);
		if (!strcmp(box_type, "ftyp"))
			fytp_read(size);
		else if (!strcmp(box_type, "moov"))
			moov_read(size);
		else
			skip_read(size);
	}






	return true;
}

int MP4File::num_read()
{
	int result;
	//mp4f->read((char*)(&result), sizeof(result));
	fread(&result, sizeof(result),1, mp4fp);
	
	return number_reverse(result);
}

short MP4File::num_read(int a)
{
	short result;
	//mp4f->read((char*)(&result), sizeof(result));
	fread(&result, sizeof(result), 1, mp4fp);
	return number_reverse(result);
}

double MP4File::num_read(float a)
{
	uint16_t result1;
	uint16_t result2;
	fread(&result1, sizeof(result1), 1, mp4fp);
	fread(&result2, sizeof(result1), 1, mp4fp);
	result1 = number_reverse((short)result1);
	result2 = number_reverse((short)result2);
	double dresult = result1;
	double x = result2;
	dresult += x / pow(10, 1 + result2 / 10);
	return dresult;
}

bool MP4File::IniMp4File(string path)
{
	//step1 ���ļ�������ļ�ͷ
	if (!OpenFile(path))
	{
		return false;
	}
	//��ȡ���֣���������ѡ����Ӧ�ĺ���
	char box_type[5];
	box_type[4] = '\0';
	int size;
	
	//ѭ������ֱ�������ļ���β
	while (!feof(mp4fp))
	{
		size = num_read();
		if (size == -858993460)
			break;
			;
		//mp4f->read(box_type, sizeof(box_type) - 1);	
		fread(box_type, sizeof(char), 4, mp4fp);
		if (!strcmp(box_type, "ftyp"))
			fytp_read(size);
		else if (!strcmp(box_type, "moov"))
			moov_read(size);
		else
			skip_read(size);
	}


	



	return true;
}






void MP4File::ShowMp4data()
{
	cout << filetype.major_brand << endl;
	cout << filetype.compatible_brands[0] << endl;
	cout << filetype.minor_version << endl;
	
}



bool MP4File::OpenFile(string path)
{
	try
	{
		mp4f = new fstream;
		mp4f->open(path, ios::binary || ios::in);
		mp4fp = fopen(path.c_str(), "rb");
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}
