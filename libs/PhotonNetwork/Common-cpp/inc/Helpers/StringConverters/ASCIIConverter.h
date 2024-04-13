/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2023 Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Common-cpp/inc/Base.h"

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			class ASCIIConverter : public Base
			{
			public:
				static char* Unicode2ASCII(const EG_CHAR* wstr, char* str, unsigned int strSize);
				static EG_CHAR* ASCII2Unicode(const char* str, EG_CHAR* wstr, unsigned int wstrLen);
			};
		}
	}
}