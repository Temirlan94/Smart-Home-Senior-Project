#install.packages("testthat")
library(testthat) 

 
source('C:/Users/pcroot/Desktop/Rprog/HumidityTests/calcHumiditySum.r')
context('testing calcHumiditySum function')

test_that('values', {
  calcHumSum<-humidity
  expect_that(calcHumSum, is_a("data.frame"))
  expect_that( length(calcHumSum), equals(1) )
 
})

test_results <- test_dir("C:/Users/pcroot/Desktop/Rprog/HumidityTests", reporter="summary")
print(test_results)
