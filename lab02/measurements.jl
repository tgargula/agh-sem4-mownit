using CSV
using DataFrames
using LinearAlgebra

d = 10
n = 10

f(x, n) = 4000 * (div(x, n) + 1)

function getDotTime(n)
    v = rand(n)
    return @elapsed dot(v, v)
end

function getMultTime(n)
    v = rand(n)
    M = rand(n, n)
    return @elapsed M * v
end

df = DataFrame(
    n = map(x -> f(x, n), 0:(d * n - 1)),
    dot_time = map(x -> getDotTime(f(x, n)), 0:(d * n - 1)), 
    mult_time = map(x -> getMultTime(f(x, n)), 0:(d * n - 1))
)

CSV.write("measurements.csv", df)