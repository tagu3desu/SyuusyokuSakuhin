
#include "main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include "audio.h"
#include"titletexturemanager.h"




IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;


void Audio::InitMaster()
{
	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&m_Xaudio, 0);

	// �}�X�^�����O�{�C�X����
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);

	
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}









void Audio::Load(const char *FileName)
{
	
	// �T�E���h�f�[�^�Ǎ�
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// �T�E���h�\�[�X����
	m_Xaudio->CreateSourceVoice(&m_SourceVoice, &wfx);
	assert(m_SourceVoice);
}


void Audio::Uninit()
{
	m_SourceVoice->Stop();
	m_SourceVoice->DestroyVoice();

	delete[] m_SoundData;
}

void Audio::Update()
{
	scene = Manager::GetScene();
	TitleTexture* titletexture = scene->GetGameObject<TitleTexture>();
}

void Audio::Volume(float vol)
{
	m_SourceVoice->SetVolume(vol);
}



void Audio::PlayBGM(bool Loop)
{
	scene = Manager::GetScene();
	TitleTexture * titletexture = scene->GetGameObject<TitleTexture>();

	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();


	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ���[�v�ݒ�
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	//Volume(titletexture->GetBGMVolume());

	//m_SourceVoice->SetVolume(titletexture->GetBGMVolume());

	/*m_BGMVolume = titletexture->GetBGMVolume();
	
	m_SourceVoice->SetVolume(m_MasterVolume*m_BGMVolume);*/

	//float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
	//m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
	//m_SourceVoice->SetVolume(0.1f);



	// �Đ�
	m_SourceVoice->Start();

}


void Audio::PlaySE()
{
	scene = Manager::GetScene();
	TitleTexture* titletexture = scene->GetGameObject<TitleTexture>();

	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();


	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	//// ���[�v�ݒ�
	//if (Loop)
	//{
	//	bufinfo.LoopBegin = 0;
	//	bufinfo.LoopLength = m_PlayLength;
	//	bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	//}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	/*m_SEVolume = titletexture->GetSEVolume();

	m_SourceVoice->SetVolume(m_MasterVolume * m_SEVolume);*/

	//float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
	//m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
	//m_SourceVoice->SetVolume(0.1f);



	// �Đ�
	m_SourceVoice->Start();

}


void Audio::Stop()
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_SourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_SourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_SourceVoice->FlushSourceBuffers();
	}
}


