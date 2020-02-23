# 함수의 순수성이 왜 중요한가 

## 순수성?

- Side Effect 가 없는 함수. Side Effect란...
  - 전역상태의 변경
  - 입력인자의 변경
  - 예외발생
  - IO 동작 : 화면 입/출력, 파일 읽기/쓰기, DB 읽기/쓰기. .....  그렇다면, 1장의 Dapper 에 대한 Wrapper는...?
- 무언가를 반환하는데, 그 값이 입력인자들에만 의존적(입력인자가 같으면 항상 동일한 값) : 입력인자만 같다면, 항상 동일한 거동을 보임. 그러면.. 
  - 병렬화가능: Share하는 상태가 없으므로, 쓰레드 안전하다.
  - 지연처리가능 : Lazy Evaluation. 값이 사용되는 시점에 ...
  - 메모이제이션 : Caching.

## Side Effect 없는 함수들을 최대한 써보기.

- I/O 되는 부분과 최대한 분리하기.
  - Pandoc예. Input File 읽어서, 변환하여, Converted File 쓰기. 
  - LOB 에서 이런일을 하기는 사실은 좀 까다로움. 이 책에서 방법을 배워봄. 

- 입력인자를 바꾸는 일을 지양하기.
  - `decimal RecomputeTotal(Order order, List<OrderLine> linesToDelete)` 를 ...
  - `(decimal, IEnumerable<OrderLine>) RecomputeTotal(Order order)` 로 바꾼다. 
  - 근데... 사실, linesToDelete를 reset하지 않았는데?
  
- 예외발생 / 전역상태변경 지양하기 : 쉽게 달성할 수 있다. 
  

## State Mutation 없애기. 

- Counter++ --> Range()
- Linq : Zip()

 그러면 AsParallel() (PLINQ)로 성능 개선 쉬움. 
 
Pure Function은  Static Method. 

- 값이 변화하는(readonly가 아닌...) Static Field 를 전혀 사용하지 않아야...
- I/O를 수행하는 다른 Static Method를 호출하지 않아야...

# Purity와 Testability

위에서 mutation은 쉽게 극복. 하지만, I/O는....**요구사항** 이므로 무시할 수 없다. 

"순수성"이란 그저 이론적인 관심대상일 뿐이다...를 타파하고 테스트 커버리지를 올리려면? 

`IDateTimeService.UtcNow` 같은 I/O혹은 외부 의존성을 Interface화 하고, 이거의 mock 혹은 su





