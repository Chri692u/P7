from lab.experiment import ARGPARSER

import os

def set_arguments():
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
        help="Domain pddl file or domain folders. --domain gripper_domain.pddl --domain gripper --domain gripper:trucks"
    )

    ARGPARSER.add_argument(
        "--problem",
        required=False,
        default="gripper_problem.pddl",
        help="Problem pddl file(s). --problem gripper_problem.pddl --problem pb1.pddl,pb2.pddl (same domain) --problem pb1.pddl:pb1.pddl (different domain)"
    )

    ARGPARSER.add_argument(
        "--reformulator",
        required=True,
        default="SameOutput",
        help="What reformulator algorithm to use"
    )

    ARGPARSER.add_argument(
        "--timelimit",
        required=True,
        default=500,
        help="Time limit for the reformulator"
    )

    return ARGPARSER.parse_args()

def abs_path(filelocation,folder):
    return os.path.join(os.path.dirname(os.path.abspath(filelocation)),folder)

def get_from_argument(argument, filelocation, defaultfolder):
    if argument:
        return argument
    else:
        return abs_path(filelocation, defaultfolder)