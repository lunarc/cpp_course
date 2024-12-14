#include "slurm_task_farm.h"

#include <iostream>

using namespace slurm;

Job::Job()
{
}

void Job::setName(const std::string &jobName)
{
    m_name = jobName;
}

void Job::setFilename(const std::string &filename)
{
    m_filename = filename;
}

void Job::setOutputFilename(const std::string &outputFilename)
{
    m_outputFilename = outputFilename;
}

void Job::setErrorFilename(const std::string &errorFilename)
{
    m_errorFilename = errorFilename;
}

void Job::setWallTime(const std::string &wallTime)
{
    m_wallTime = wallTime;
}

void Job::setNTasks(const std::string &nTasks)
{
    m_nTasks = nTasks;
}

void Job::setCpusPerTask(const std::string &cpusPerTask)
{
    m_cpusPerTask = cpusPerTask;
}

void Job::setMemPerCpu(const std::string &memPerCpu)
{
    m_memPerCpu = memPerCpu;
}

void Job::setPartition(const std::string &partition)
{
    m_partition = partition;
}

void Job::setMailType(const std::string &mailType)
{
    m_mailType = mailType;
}

void Job::setMailUser(const std::string &mailUser)
{
    m_mailUser = mailUser;
}

std::string Job::name() const
{
    return m_name;
}

std::string Job::filename() const
{
    return m_filename;
}

std::string Job::outputFilename() const
{
    return m_outputFilename;
}

std::string Job::errorFilename() const
{
    return m_errorFilename;
}

std::string Job::wallTime() const
{
    return m_wallTime;
}

std::string Job::nTasks() const
{
    return m_nTasks;
}

std::string Job::cpusPerTask() const
{
    return m_cpusPerTask;
}

std::string Job::memPerCpu() const
{
    return m_memPerCpu;
}

std::string Job::partition() const
{
    return m_partition;
}

std::string Job::mailType() const
{
    return m_mailType;
}

std::string Job::mailUser() const
{
    return m_mailUser;
}

void Job::addModule(const std::string &module)
{
    m_modules.push_back(module);
}

StringList &Job::modules()
{
    return m_modules;
}

void Job::clearModules()
{
    m_modules.clear();
}

void Job::generateScript()
{
    doGenerateScript();
}

void slurm::Job::addMainScript(const std::string &line)
{
    m_mainScript.push_back(line);
}

void slurm::Job::clearMainScript()
{
    m_mainScript.clear();
}

void slurm::Job::addSlurmScript(const std::string &line)
{
    m_slurmScript.push_back(line);
}

void slurm::Job::addJobProperty(const std::string &property, const std::string &value)
{
    if (!value.empty())
        addSlurmScript("#SBATCH --" + property + "=" + value);
}

void slurm::Job::addModuleLine(const std::string &module)
{
    addSlurmScript("module load " + module);
}

StringList &slurm::Job::slurmScript()
{
    return m_slurmScript;
}

StringList &slurm::Job::mainScript()
{
    return m_mainScript;
}

std::string slurm::Job::script()
{
    generateScript();
    std::string script;
    for (const auto &line : m_slurmScript)
        script += line + "\n";
    for (const auto &line : m_mainScript)
        script += line + "\n";
    return script;
}

void slurm::Job::print()
{
    for (const auto &line : m_slurmScript)
        std::cout << line << std::endl;
}

void slurm::Job::doWriteHeader()
{
    addSlurmScript("#!/bin/bash");
}

void slurm::Job::doWriteJobProperties()
{
    addJobProperty("job-name", name());
    addJobProperty("output", outputFilename());
    addJobProperty("error", errorFilename());
    addJobProperty("time", wallTime());
    addJobProperty("ntasks", nTasks());
    addJobProperty("cpus-per-task", cpusPerTask());
    addJobProperty("mem-per-cpu", memPerCpu());
    addJobProperty("partition", partition());
    addJobProperty("mail-type", mailType());
    addJobProperty("mail-user", mailUser());
    addSlurmScript("");
}

void slurm::Job::doWriteModules()
{
    for (const auto &module : m_modules)
        addModuleLine(module);
    addSlurmScript("");
}

void slurm::Job::doWriteMain()
{
    for (const auto &line : m_mainScript)
        addSlurmScript(line);
}

void Job::doGenerateScript()
{
    m_slurmScript.clear();

    doWriteHeader();
    doWriteJobProperties();
    doWriteModules();
    doWriteMain();
}
