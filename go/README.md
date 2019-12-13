# Go Lang 메모

## 기초 학습

- [Go 프로그래밍 언어 소개 - 예제로 배우는 Go 프로그래밍](http://golang.site/Go/Basics)
- [Go 활용 - 예제로 배우는 Go 프로그래밍](http://golang.site/Go/Applications)
- [Effective Go - golang.org](https://golang.org/doc/effective_go.html#composite_literals) 
- [Effective Go 한글 - github](https://github.com/golangkorea/effective-go) : [GitBook에서 pdf 를 다운받거나 읽을 수 있다](https://legacy.gitbook.com/book/gosudaweb/effective-go-in-korean/details) . 
- [Go Tutotorial Video - Youtube](https://www.youtube.com/watch?v=YS4e4q9oBaU)

기초라고 하기는 어렵지만, 학습중 좀 심오한 내용이 알 고 싶을 때는 다음 참조.

- [Go Language Spec - golang.org](https://golang.org/ref/spec)



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

## `for` 순환문의 4가지 사용패턴.

- https://yourbasic.org/golang/for-loop-range-array-slice-map-channel/

## Slice와 Array 에 대한 상세 내용

https://blog.golang.org/go-slices-usage-and-internals

- Array는 Value Type 이어서, 다른 변수에 대입하거나 인자로 넘겨질 때, 전체가 복제된다. 
- Slice는 3개의 값(Array에 대한 Pointer + Length + Capacity)으로 구성된  Value Type. 
- Slice Operator는 `aSomeArray[1:4]` 와 같이 쓰지만, 범위가 0보다 작은 것을 넣을 수 없다. 
  
Slice가 참조하는 Array는, 극히 일부분만 가리키고 있더라도, Array 전체가 메모리에 유지된다. 

```go
var digitRegexp = regexp.MustCompile("[0-9]+")

func FindDigits(filename string) []byte {
    b, _ := ioutil.ReadFile(filename)
    return digitRegexp.Find(b)
}
```

위 코드는 파일을 읽어서 연속된 숫자들이 있는 부분을 찾는데, 파일사이즈가 크고, 찾은게 1~2 byte밖에 안되어도, 전체 파일에 대한 메모리가 유지된다(Slice에 의해 참조되고 있기 때문). 아래와 같이 개선할 수 있다. 

```go
func CopyDigits(filename string) []byte {
    b, _ := ioutil.ReadFile(filename)
    b = digitRegexp.Find(b)
    c := make([]byte, len(b))
    copy(c, b)
    return c
}
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


