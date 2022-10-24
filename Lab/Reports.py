from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport

import os

def add_reports(experiment):
    add_parsers(experiment)

    ERROR_ATTRIBUTES= ['domain', 
                       'problem', 
                       'algorithm', 
                       'unexplained_errors', 
                       'error', 
                       'planner_wall_clock_time', 
                       'raw_memory', 
                       'node']

    PREDEFINED_ATTRIBUTES= ['cost', 
                            'coverage', 
                            'dead_ends', 
                            'evaluations', 
                            'expansions', 
                            'generated', 
                            'initial_h_value', 
                            'plan_length', 
                            'planner_time', 
                            'quality', 
                            'score_*', 
                            'search_time', 
                            'total_time', 
                            'unsolvable']

    ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES
    experiment.add_report(AbsoluteReport(attributes=ATTRIBUTES), outfile="report.html")

    EXTRA = ["parsing_pddl", 
                  "converison_of_pddl_format", 
                  "reformulation_of_pddl", 
                  "generating_pddl",
                  "running_fastdownward",
                  "parse_sas_plan",
                  "rebuild_sas_plan",
                  "output_sas_plan"]

    MS = [x+"_ms" for x in EXTRA]
    add_taskwisereport(experiment, "report_ms.html", MS)
    
    PROCENT = [x+"_procent" for x in EXTRA]
    add_taskwisereport(experiment, "report_procent.html", PROCENT)

def add_taskwisereport(experiment, name, attributes):
    experiment.add_report(TaskwiseReport(attributes=attributes), outfile=name)

def add_parsers(experiment):
    EXITCODE_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"ExitcodeParser.py")
    TRANSLATOR_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"TranslatorParser.py")
    SINGLE_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"SingleSearchParser.py")
    PLANNER_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"PlannerParser.py")
    ANYTIME_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"AnytimeSearchParser.py")
    P7_LAB_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)),"P7LabParser.py")

    experiment.add_parser(EXITCODE_PARSER)
    experiment.add_parser(TRANSLATOR_PARSER)
    experiment.add_parser(SINGLE_SEARCH_PARSER)
    experiment.add_parser(PLANNER_PARSER)
    experiment.add_parser(ANYTIME_SEARCH_PARSER)
    experiment.add_parser(P7_LAB_PARSER)