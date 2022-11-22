add_executable(P7 "P7.cpp")
target_link_libraries(P7 
    PRIVATE
        PlanGenerator
        RunReport
        Config
        StringHelper
        ConsoleHelper
        FileVerifier
        PathChecker
        PDDLCodeGenerator
        CommonInterface
        PlanValidator
        Reformulator
        SASParser
        SASCodeGenerator
        PDDLParser
        IntermediatePDDL
        PathChecker
        DownwardRunner
        FileHelper
        Walker
        EntanglementFinder
        ActionGenerator
        Hashes
        ProgressBarHelper
        MacroGenerator)

add_executable(P7Lab "P7Lab.cpp")
