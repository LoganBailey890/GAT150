
#include "AudioChannel.h"

namespace nc
{
	bool AudioChannel::IsPlaying()
	{
		if (channel == nullptr) return false;

		bool isPlaying;
		channel->isPlaying(&isPlaying);

		return isPlaying;
	}
	void AudioChannel::Stop()
	{
		if (IsPlaying())
		{

			channel->stop();
		}
	}
	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying())
		{
			channel->setPitch(pitch);
		}
	}
	float AudioChannel::GetPitch()
	{
		if (IsPlaying())
		{
			float pitch =0;
			channel->getPitch(&pitch);
			return pitch;
		}
	}
	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying())
		{
			channel->setVolume(volume);
		}
	}
	float AudioChannel::GetVolume(float volume)
	{
		if (IsPlaying())
		{
			float volume= 0;
			channel->getPitch(&volume);
			return volume;
		}
	}
}