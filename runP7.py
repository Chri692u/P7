#! /usr/bin/env python

from lab.experiment import Experiment
from lab.experiment import ARGPARSER
from downward.reports.absolute import AbsoluteReport
from downward.reports.taskwise import TaskwiseReport
import shutil
import os
from os import path

ARGPARSER.add_argument(
    "--report",
    required=False,
    help="Foldername for report and eval"
)

ARGPARSER.add_argument(
    "--P7",
    required=False,
    help="Path to project P7 executable"
)

ARGPARSER.add_argument(
    "--downward",
    required=True,
    help="Path to Fast Downward"
)

ARGPARSER.add_argument(
    "--validate",
    required=True,
    help="Path to VAL"
)

ARGPARSER.add_argument(
    "--search",
    required=False,
    default="astar",
    help="Search Fast Downward should use. Ex. astar"
)

ARGPARSER.add_argument(
    "--evaluator",
    required=False,
    default="blind",
    help="Evaluator Fast Downward should use. Ex. blind"
)

ARGPARSER.add_argument(
    "--benchmarks",
    required=False,
    help="Folder where problems are in"
)

ARGPARSER.add_argument(
    "--domain",
    required=False,
    default="gripper_domain.pddl",
    help="Domain pddl file"
)

ARGPARSER.add_argument(
    "--problem",
    required=False,
    default="gripper_problem.pddl",
    help="Problem pddl file"
)

args = ARGPARSER.parse_args()

reportfolder = args.report if args.report else os.path.join(os.path.dirname(os.path.abspath(__file__)),"build/LabReport")

projectfile = args.P7 if args.P7 else os.path.join(os.path.dirname(os.path.abspath(__file__)),"build/P7")
downwardfilepath = args.downward
validatorfilepath = args.validate

search = args.search
evaluator = args.evaluator

benchmarksfolder = args.benchmarks if args.benchmarks else os.path.join(os.path.dirname(os.path.abspath(__file__)),"Data/Classical tracks/Gripper/")
domain = args.domain
problem = args.problem

experiment = Experiment(reportfolder)

arguments = [os.path.join(os.path.dirname(os.path.abspath(__file__)), projectfile)]
arguments += ["-d", benchmarksfolder + domain]
arguments += ["-p", benchmarksfolder + problem]
arguments += ["-f", downwardfilepath]
arguments += ["-v", validatorfilepath]
arguments += ["-s", search]
arguments += ["-e", evaluator]

run = experiment.add_run()
run.add_command("planner", arguments)
run.set_property("id",[search, evaluator, domain, problem])
run.set_property("domain", domain)
run.set_property("problem", problem)
run.set_property("algorithm", search + "(" + evaluator + ")")

if path.exists(reportfolder):
    experiment.add_step("rm-exp-dir", shutil.rmtree, reportfolder)
if path.exists(experiment.eval_dir):
    experiment.add_step("rm-eval-dir", shutil.rmtree, experiment.eval_dir)
experiment.add_step("build", experiment.build)
experiment.add_step("start", experiment.start_runs)
experiment.add_fetcher(name="fetch")

EXITCODE_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/ExitcodeParser.py")
TRANSLATOR_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/TranslatorParser.py")
SINGLE_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/SingleSearchParser.py")
PLANNER_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/PlannerParser.py")
ANYTIME_SEARCH_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/AnytimeSearchParser.py")
P7_LAB_PARSER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Lab/P7LabParser.py")

experiment.add_parser(EXITCODE_PARSER)
experiment.add_parser(TRANSLATOR_PARSER)
experiment.add_parser(SINGLE_SEARCH_PARSER)
experiment.add_parser(PLANNER_PARSER)
experiment.add_parser(P7_LAB_PARSER)

ERROR_ATTRIBUTES= ['domain', 'problem', 'algorithm', 'unexplained_errors', 'error', 'planner_wall_clock_time', 'raw_memory', 'node']
PREDEFINED_ATTRIBUTES= ['cost', 'coverage', 'dead_ends', 'evaluations', 'expansions', 'generated', 'initial_h_value', 'plan_length', 'planner_time', 'quality', 'score_*', 'search_time', 'total_time', 'unsolvable']
ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES

#format can be tex for reports
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
PROCENT = [x+"_procent" for x in EXTRA]

experiment.add_report(TaskwiseReport(attributes=(MS)), outfile="report_ms.html")
experiment.add_report(TaskwiseReport(attributes=(PROCENT)), outfile="report_procent.html")

experiment.run_steps()