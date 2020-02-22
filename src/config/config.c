/*
 * config.c
 *
 *  Created on: Feb 22, 2020
 *      Author: chrisblust
 */

#ifndef CONFIG_DISABLE_RATIONALITY_CHECK
#define CONFIG_RATIONALITY_CHECK 1
#else
#define CONFIG_RATIONALITY_CHECK 0
#endif

int config_rationality_check_enabled(void)
{
	return CONFIG_RATIONALITY_CHECK;
}

#ifndef CONFIG_DISABLE_TEMP_MONITORING
#define CONFIG_TEMP_MONITORING 1
#else
#define CONFIG_TEMP_MONITORING 0
#endif

int config_temp_monitoring_enabled(void)
{
	return CONFIG_TEMP_MONITORING;
}


