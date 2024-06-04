//
// Created by 86158 on 2024/6/4.
//

#ifndef ZEARO_BASH_ALIAS_H
#define ZEARO_BASH_ALIAS_H

#include <unordered_map>
#include <string>

class alias {
private:
    std::unordered_map<std::string, std::string> aliasMap;

private:
    // private constructor
    alias() = default;

    ~alias() = default;

    static alias* instance;

public:
    // delete copy for single instance
    const alias &operator=(const alias& _) = delete;
    alias(const alias& _) = delete;

public:
    /**
     * @brief get the only instance of this class.
     * @return
     */
    static alias* getInstance();

    void initFromTheFile(const char* fileName);

    void writeTheMapIntoFile();

    void printTheMap();

    /**
     * @brief add alia to the map
     * @param originName
     * @param aliasName
     * @return status code, 1 success, 0 fail
     */
    int addAlias(const std::string& originName, const std::string& aliasName);

    /**
     * @brief remove alia from the map
     * @param aliasName
     * @return status code, 1 success, 0 fail
     */
    int removeAlias(const std::string& aliasName);
};

#endif //ZEARO_BASH_ALIAS_H
