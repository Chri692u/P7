from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport

import json
import csv

import os
from os import path

ERROR_ATTRIBUTES= ['domain', 
                    'problem', 
                    'algorithm', 
                    'unexplained_errors', 
                    'error', 
                    'raw_memory',
                    'settings_file']

PREDEFINED_ATTRIBUTES= ['cost', 
                        'coverage', 
                        'dead_ends', 
                        'evaluations', 
                        'expansions', 
                        'generated', 
                        'initial_h_value', 
                        'plan_length', 
                        'planner_time', 
                        'search_time', 
                        'unsolvable',
                        'translator_facts',
                        'p7_solving_problem_ms',
                        'p7_validating_reformulated_plan_notes',
                        'p7_validating_rebuilded_plan_notes',
                        'p7_solving_problem_notes',
                        'p7_rebuild_sas_plan_notes',
                        'p7_parse_sas_plan_notes']

ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES

def add_absolute_report(experiment):
    experiment.add_report(AbsoluteReport(attributes=ATTRIBUTES), outfile="report.html")

def add_csv_report(experiment):
    basePath = os.path.dirname(__file__)
    if path.exists(os.path.join(basePath, "../LabReports/")):
        print("Generating csv file")
        outputCSVFileName = os.path.join(basePath, "../LabReports/report.csv")
        outputCSVFile = open(outputCSVFileName, 'w')
        outputCSVWriter = csv.writer(outputCSVFile)

        outputCSVWriter.writerow(ATTRIBUTES)

        reports = os.listdir(os.path.join(basePath, "../LabReports/"))
        count = 0
        for folder in reports:
            propertiesFileName = os.path.join(basePath, "../LabReports/" + folder + "/properties")
            if os.path.isfile(propertiesFileName):
                propertiesFile = open(propertiesFileName)
                jsonData = json.load(propertiesFile)

                for key in jsonData:
                    row = [" "] * len(ATTRIBUTES)
                    for checkKey in jsonData[key]:
                        if checkKey in ATTRIBUTES:
                            row[ATTRIBUTES.index(checkKey)] = jsonData[key][checkKey]
                    outputCSVWriter.writerow(row)

                propertiesFile.close()
                count += 1

        print("Combined a total of " + str(count) + " reports.")

        outputCSVFile.close()

def add_taskwise_reports(experiment, reformulators):
    for reformulator in reformulators:
        experiment.add_report(TaskwiseReport(attributes=["*_ms"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_ms.html")
        experiment.add_report(TaskwiseReport(attributes=["*_procent"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_procent.html")
        experiment.add_report(TaskwiseReport(attributes=["*_notes"],filter_algorithm=[reformulator]), outfile=reformulator+"_report_notes.html")

def add_parsers(experiment):
    EXITCODE_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"ExitcodeParser.py")
    PLANNER_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"PlannerParser.py")

    TRANSLATOR_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"TranslatorParser.py")
    SINGLE_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"SingleSearchParser.py")
    ANYTIME_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"AnytimeSearchParser.py")
    P7_LAB_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"P7LabParser.py")

    #reads from the driver.log file
    experiment.add_parser(EXITCODE_PARSER)

    #reads from the downwardLog file
    experiment.add_parser(SINGLE_SEARCH_PARSER)
    experiment.add_parser(ANYTIME_SEARCH_PARSER)

    experiment.add_parser(TRANSLATOR_PARSER)
    experiment.add_parser(P7_LAB_PARSER)

    #reads from the driver.log but needs coverage in properties file that AnytimeSearchParser or SingleSearchParser gives
    experiment.add_parser(PLANNER_PARSER)