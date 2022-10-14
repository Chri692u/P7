"""
Example of output

Running reformulator...
Parsing PDDL files...   ✓ 0ms
Converting PDDL format...   ✓ 0ms
Reformulating PDDL...Note, this reformulator is only for testing! Simply gives the same result back.
   ✓ 0ms
Generating PDDL files...   ✓ 0ms
Run new PDDL files with Fast Downward...   ✓ 120ms
Parse SAS Plan...   ✓ 0ms
Rebuild the SAS plan...   ✓ 0ms
Output new SAS Plan...   ✓ 0ms
Done!
---- Time Taken ----
Description               Time Taken (ms) Time Taken (%)
Parsing PDDL              0.684           0.559
Converison of PDDL format 0.267           0.218
Reformulation of PDDL     0.002           0.002
Generating PDDL           0.513           0.419
Running FastDownward      120.452         98.423
Parse SAS plan            0.308           0.251
Rebuild SAS plan          0.035           0.029
Output SAS plan           0.121           0.099
Total Time                122.382
"""

import re
from lab.parser import Parser

def get_times(content, props):
    stages = ["parsing_pddl", 
              "converison_of_pddl_format", 
              "reformulation_of_pddl", 
              "generating_pddl",
              "running_fastdownward",
              "parse_sas_plan",
              "rebuild_sas_plan",
              "output_sas_plan"]
    all_times = re.findall(r"(\d+\.\d+)", content)
    times = all_times[::2]
    procents = all_times[1::2]

    for index in range(len(stages)):
        props[stages[index]+"_ms"] = times[index]
        props[stages[index]+"_procent"] = procents[index]

    """
    props["parsing_pddl_ms"] = times[0]
    props["converison_of_pddl_format"] = times[2]
    props["reformulation_of_pddl"] = times[4]
    props["generating_pddl"] = times[6]
    props["running_fastdownward"] = times[8]
    props["parse_sas_plan"] = times[10]
    props["rebuild_sas_plan"] = times[12]
    props["output_sas_plan"] = times[14]
    """

parser = Parser()
parser.add_function(get_times, file="run.log")
parser.parse()
