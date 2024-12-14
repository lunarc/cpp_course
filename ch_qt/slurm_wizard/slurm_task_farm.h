#pragma once

#include <string>
#include <vector>

namespace slurm
{

typedef std::vector< std::string > StringList;

class Job {
private:
    std::string m_name{"Noname"};
    std::string m_filename{"jobscript.sh"};
    std::string m_outputFilename{"job.out"};
    std::string m_errorFilename{"job.err"};
    std::string m_wallTime{"00:30:00"};
    std::string m_nTasks{"4"};
    std::string m_cpusPerTask{"1"};
    std::string m_memPerCpu{""};
    std::string m_partition{""};
    std::string m_mailType{""};
    std::string m_mailUser{""};

    StringList m_modules;
    StringList m_slurmScript;
    StringList m_mainScript;

public:
    Job();
    void setName(const std::string &jobName);
    void setFilename(const std::string &filename);
    void setOutputFilename(const std::string &outputFilename);
    void setErrorFilename(const std::string &errorFilename);
    void setWallTime(const std::string &wallTime);
    void setNTasks(const std::string &nTasks);
    void setCpusPerTask(const std::string &cpusPerTask);
    void setMemPerCpu(const std::string &memPerCpu);
    void setPartition(const std::string &partition);
    void setMailType(const std::string &mailType);
    void setMailUser(const std::string &mailUser);
    std::string name() const;
    std::string filename() const;
    std::string outputFilename() const;
    std::string errorFilename() const;
    std::string wallTime() const;
    std::string nTasks() const;
    std::string cpusPerTask() const;
    std::string memPerCpu() const;
    std::string partition() const;
    std::string mailType() const;
    std::string mailUser() const;

    void addModule(const std::string &module);
    StringList &modules();
    void clearModules();

    void generateScript();

    void addMainScript(const std::string &line);
    void clearMainScript();

    void addSlurmScript(const std::string &line);
    void addJobProperty(const std::string &property, const std::string &value);
    void addModuleLine(const std::string &module);
    StringList &slurmScript();
    StringList &mainScript();

    std::string script();

    void print();

protected:
    virtual void doWriteHeader();
    virtual void doWriteJobProperties();
    virtual void doWriteModules();
    virtual void doWriteMain();
    virtual void doGenerateScript();
};

} // namespace slurm
