
from aifc import Error
from downward.suites import Problem

def get_suite(domains, problemsindomains):
    suite = []
    for domainindex in range(len(domains)):
        domain = domains[domainindex]
        print(domain)
        if len(problemsindomains) != len(domains):
            suite.append(domain)
        else:
            domainproblems = problemsindomains[domainindex].split(",")
            for problem in domainproblems:
                if problem:
                    print(problem)
                    suite.append(domain+":"+problem)
                else:
                    suite.append(domain)
    return suite

def make_tasks(benchmarksfolder, domains, problemsindomains):
    tasks = []
    for domainindex in range(len(domains)):
        domain = domains[domainindex]
        print(domain)
        if len(problemsindomains) != len(domains):
            raise Error("There are not defined problems for some domains")
        else:
            domainproblems = problemsindomains[domainindex].split(",")
            for problem in domainproblems:
                if problem:
                    print(problem)
                    tasks.append(Problem(domain, 
                                         problem, 
                                         benchmarksfolder + problem, 
                                         benchmarksfolder + domain))
                else:
                    raise Error("Missing problem file")
    return tasks