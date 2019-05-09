#install.packages("DBI")
#install.packages("RMySQL")
#install.packages("ggplot2")

library(ggplot2)
library(DBI)
library(RMySQL)
#Database Connection and Retrivieng Values
#======================================================================
#======================================================================
connectionResult<-function()
{
  con<-dbConnect(MySQL(),host="localhost",dbname="anildata",user="root",password="")
  
  return (con)
}

test.connectionResult<-function()
{
  dbIsValid(con)
  isIdCurrent(con)
  return(print(isIdCurrent(con)))
  
}

con=connectionResult()
conStatus=test.connectionResult()

#test.dataRetrieveResult<-function()
#{
  result=dbSendQuery (con,"select * from temphum")
  data=fetch(result,n=-1)
  temperature=subset(data,select=c(temperature))
 
 # return (temperature)
#}

#temp=test.dataRetrieveResult()
print(temperature)



dbClearResult(result)
dbDisconnect(con)


