//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H

namespace MackieOfTheUnicorn::Views
{
	class MackieViewData
	{
	  public:
		virtual ~MackieViewData() = default;
		virtual void SetMute(int channelId, bool on) = 0;
		virtual bool GetMute(int channelId) = 0;
		virtual void SetSolo(int channelId, bool on) = 0;
		virtual bool GetSolo(int channelId) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H
