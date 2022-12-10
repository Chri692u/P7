NB. for debugging in J
require 'debug/dissect'

NB. for plotting data
require 'graphics/plot'

NB. for working with css
require 'tables/dsv'
require 'tables/csv'

NB. Data
report =: readcsv '../git/P7/build/LabReports/report.csv'
fields =: {.report
csvData =: }.report
rows =: #csvData

NB. Data points
problems =: 1
algorithm =: 2
expansions =: 11

NB. Main verbs
DataOf =: {{(y {/"1 x)}}
AlgoMask =: {{,((x DataOf algorithm) = <y)}}
Isolate =: {{((csvData AlgoMask y)#i.rows) { x}}
Elements =: {{".(>(,x DataOf y))}}

NB. Workspace
NB. Vi splitter csv filen op på de algoritmer vi vil have
sameoutput =: csvData Isolate 'sameoutput'
greedyWalker =: csvData Isolate 'greedyWalker'

greedyWalker

NB. Vi trækker det ud af csv-delene som vi leder efter (expansions her)
sameoutput_expansions =: sameoutput Elements expansions
greedyWalker_expansions =: greedyWalker Elements expansions

NB. Vi kan bruge J-Magi til at arbejde på listerne
sameoutput_expansions > greedyWalker_expansions
NB. (f.eks finde ud af hvor mange gange vores havde mindre expansions)
+/sameoutput_expansions > greedyWalker_expansions

NB. Og vi kan plot dem op imod hinanden (x aksen er hvert index i begge arrays)
(<sameoutput_expansions) plot <greedyWalker_expansions
