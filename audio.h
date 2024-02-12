#pragma once

#include <xaudio2.h>
#include "gameObject.h"


class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

	float m_MasterVolume = 0.1f;
	

	class Scene* scene{};
public:
	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Uninit();
	void Update();

	void Load(const char *FileName);
	void PlayBGM(bool Loop = true);
	void PlaySE();
	void Volume(float vol);
	void Stop();

};

