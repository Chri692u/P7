#! /usr/bin/env python

from lab.experiment import Experiment
from downward import suites
import shutil
from os import path
from Lab.Reports import *
from Lab.Benchmarks import get_suite, make_tasks
from Lab.ConfigParser import *

print("Parsing Lab Settings file")
linesLab = []
with open("settingsLab.ini", 'r') as file:
    for line in file.readlines():
        if not line.lstrip(" ").startswith(";"):
            linesLab.append(line)

settingsFiles = []
for line in linesLab:
    if "SettingsCollection" in line:
        settingsFiles = line.split("=")[1].strip("\n").split(",")

experiments = []

basePath = os.path.dirname(__file__)
if path.exists("LabReports/"):
    shutil.rmtree("LabReports/")

print("Found a total of " + str(len(settingsFiles)) + " settings files to run")

for settingsFile in settingsFiles:
    print("Begining run of settings file " + settingsFile)

    if ".ini" not in settingsFile:
        settingsFile = settingsFile + ".ini"
    fileContent = get_config("LabSettings/" + settingsFile)

    search = ""
    heuristic = ""
    domainline = ""
    problemline = ""
    reformulators = []

    reportline = ""
    projectline = ""

    settingscontent = ""

    #Parse config file and remove lab specific settings
    for line in fileContent:
        if "downwardsearch" in line:
            search = line.split("=")[1].strip("\n")
            settingscontent += line
        elif "downwardheuristic" in line:
            heuristic = line.split("=")[1].strip("\n")
            settingscontent += line
        elif "domain" in line:
            domainline = line.split("=")[1].strip("\n")
        elif "problem" in line:
            problemline = line.split("=")[1].strip("\n")
        elif "report" in line:
            reportline = line.split("=")[1].strip("\n")
        elif "project" in line:
            projectline = line.split("=")[1].strip("\n")
        elif "downward" in line or "validator" in line:
            argument = line.split("=")
            settingscontent += argument[0] + "=" + os.path.join(basePath, argument[1]) 
        elif "reformulator=" in line:
            reformulators = line.split("=")[1].strip("\n").split(",")
        elif "EXTERNAL" not in line:
            settingscontent += line

    
    #if not found in config file the default values are used
    reportfolder = os.path.join(basePath, 'LabReport')
    projectfile = os.path.join(basePath, 'src/P7')

    #decide if labs method to find domains and problems should be used
    #since lab wants the benchmarksfolder to have a specific structure
    lab_build_suite = True
    benchmarksfolder = os.path.join(basePath, "Data/benchmarks/")

    domains = domainline.split(":")
    problemsindomains = problemline.split(":")

    experiment = Experiment(reportfolder)

    tasks = []
    tasks = suites.build_suite(benchmarksfolder, get_suite(domains, problemsindomains))

    """
    Each task contains a domain file and problem file
    For each task a settings.ini file is made and P7 is given this file as argument
    """
    for reformulator in reformulators:
        for task in tasks:
            content = settingscontent
            content += "\nPATH:domain=" + task.domain_file + "\n"
            content += "PATH:problem=" + task.problem_file + "\n"

            content += "LIST<STRING>:reformulator=" + reformulator + "\n"

            run = experiment.add_run()
            run.add_new_file("config","TempSettings.ini",content)
            run.add_command("planner", [projectfile,"{config}"])

            run.set_property("id",[reformulator, task.domain, task.problem])
            run.set_property("domain", task.domain)
            run.set_property("problem", task.problem)
            run.set_property("algorithm", reformulator)
            run.set_property("settings_file", settingsFile.replace(".ini",""))

    experiment.set_property("settings_file", settingsFile.replace(".ini",""));
    if path.exists(reportfolder):
        experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
    if path.exists(experiment.eval_dir):
        experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
    if path.exists("LabReports/" + settingsFile.replace(".ini","")):
        experiment.add_step("rm-report-dir", shutil.rmtree, "LabReports/" + settingsFile.replace(".ini",""))
    experiment.add_step("build", experiment.build)
    experiment.add_step("start", experiment.start_runs)
    experiment.add_fetcher(name="fetch")

    add_parsers(experiment)
    add_absolute_report(experiment)
    add_taskwise_reports(experiment, reformulators)

    for reformulator in reformulators:
        if (reformulator != "sameoutput"):
            add_scatterplot_report(experiment, reformulator)

    experiment.run_steps()

    shutil.move(experiment.eval_dir, "LabReports/" + settingsFile.replace(".ini",""))

    experiments.append(experiment)

add_csv_report(experiments)