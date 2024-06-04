//
// Created by 86158 on 2024/6/3.
//

#ifndef ZEARO_BASH_CONFIGS_H
#define ZEARO_BASH_CONFIGS_H

#ifndef ZEARO_BASH_HISTORY_FILE
#define ZEARO_BASH_HISTORY_FILE ".zbash_history"
#endif


#ifndef ZEARO_BASH_CONFIGS_FILE
#define ZEARO_BASH_CONFIGS_FILE ".zbash_configs"
#endif

#ifndef ZEARO_BASH_CONFIGS_ALIAS
#define ZEARO_BASH_CONFIGS_ALIAS "alias"
#endif

/**
 * @brief load zearo bash configs.
 */
extern void loadConfigs();


#endif //ZEARO_BASH_CONFIGS_H
