#install.packages("testthat")

library(testthat) 
source('C:/Users/pcroot/Desktop/Rprog/temperaturesTests/calcTempSum.r')
context('testing calcTempSum function')

test_that('values', {
  calcTempSum<-temp
  expect_that(calcTempSum, is_a("data.frame"))
  expect_that( length(calcTempSum), equals(1) )
})

test_results <- test_dir("C:/Users/pcroot/Desktop/Rprog/temperaturesTests", reporter="summary")
print(test_results)



