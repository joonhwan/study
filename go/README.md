# Go Lang 메모

## 기초 학습

- [Go 프로그래밍 언어 소개 - 예제로 배우는 Go 프로그래밍](http://golang.site/Go/Basics)
- [Go 활용 - 예제로 배우는 Go 프로그래밍](http://golang.site/Go/Applications)
- [Effective Go - golang.org](https://golang.org/doc/effective_go.html#composite_literals)
- [Go Tutotorial Video - Youtube](https://www.youtube.com/watch?v=YS4e4q9oBaU)
 
##  메모

## golang 에서 `...`(점 3개!)가 사용되는 경우  : [REF](https://yourbasic.org/golang/three-dots-ellipsis/)

### 가변인자 함수
```go
func Sum(nums ...int) int {
    res := 0
    for _, n := range nums {
        res += n
    }
    return res
}
```
### 가변인자 함수 호출시 변수 unpack

아래 예는 정수 slice 를 인자로 넘기는게 아니라, `2, 3, 5, 7` 의 값 4개를 각각 독립된 인자로 함수에 넘긴다. 

```go
primes := []int{2, 3, 5, 7}
fmt.Println(Sum(primes...)) // 17
```

### Array Literal

`slice` 가 아니라 `array` 를 만들때, 갯수를 자동으로 지정되게 함

```go
stooges := [...]string{"Moe", "Larry", "Curly"} // len(stooges) == 3
```

### go 명령어

go 명령어에서 `...` 는 패키지 목록을 지정할 때 wildcard 처럼 쓰인다. 
이를테면 다음 명령은 현재 디렉토리 및 모든 하위 디렉토리에 있는 모든 패키지들을 테스트 한다. 

```
$ go test ./...
```


## make() 와 new() 차이 - [REF](https://www.godesignpatterns.com/2014/04/new-vs-make.html)

- new() 는 zero value 된 메모리(='zeroed storage')를 *포인터 형태* 로 반환

```go
// Allocate enough memory to store a bytes.Buffer value
// and return a pointer to the value's address.
var buf bytes.Buffer
p := &buf

// Use a composite literal to perform allocation and
// return a pointer to the value's address.
p := &bytes.Buffer{}

// Use the new function to perform allocation, which will
// return a pointer to the value's address.
p := new(bytes.Buffer)
```

- make() 는 특별한 방법으로 초기화된(?) 메모리를 *포인터가 아닌 형태*로 반환 --> `map`, `slice`, `chan` ...


```go
// Using make() to initialize a map.
m := make(map[string]bool, 0)

// Using a composite literal to initialize a map.
m := map[string]bool{}
```


