# 시작하기 

원래 비디오는 vs2017 을 쓰지만 난 vscode를 썼다. 
그리고 비디오가 녹화된 것을 보면 대략 2017년 11월경쯤인거 같고, 화면상에서는 .net core 2.0 버젼대를 사용하는것 같았다. 
(실제로 이글을 작성하는 시점의 최신버젼은 2.2 인데, 이버젼은 사용자에게 드러난 코드들을 상당수 라이브러리로 옮겨놔서 안의 구현을 보기도 쉽지 않고, 설명을 따라하기도 쉽지 않다. 일단, 배우기 위해 2.0버젼대를 쓰는게 좋은 것 같다.)


그래서...

   - [dotnet core 2.0.3 릴리즈 페이지](https://github.com/dotnet/core/blob/master/release-notes/download-archives/2.0.3.md) 에서 SDK Installer를 받아 설치
   - global.json 파일을 디렉토리에 넣어서 2.0.3 을 사용하도록 설정.

하였다. 디렉토리 만들고, 거기서 global.json을 넣어두었다. 그러니 그 디렉토리에서 `dotnet --version` 하면 2.0.3으로 나오는 지 확인한다. 

프로젝트 만들때, 비디오는 vs2017 사용. 나는 커맨드라인에서 생성하고 싶으니... 

```
dotnet new razor --auth Individual -n mymva -o aspnet-core-intermediate-video-follow-up
```

사실 `dotnet new` 로 만들수 있는거는 여러개가 있는데, vs2017에서 web app을 선택하면, mvc가 아니라 razor page로 만들어진 web app을 만든다. 

이건.. `dotnet new razor --help` 하면 나오는 옵션들 설명을 읽고 선택한거.

이렇게 해도 완전히 비디오와 같지는 않다.

   -  vs2017 에서 해당 프로젝트 위자드는 SqlServer를  db로 사용, dotnet new로 만든거는 sqlite 사용.
   -  Startup.Configure() 에서 BrowserLink 를 활성화하지 않았다(dotnet new razor 할때 옵션을 주면 이거도 기본으로 들어갈 듯...확인은 안해봄.)

# StartUp.cs 설명

Main()함수에서는 IWebHostBuilder인터페이스를 제공하는 객체를 하나 만들고, 
이 인터페이스를 통해서 몇가지 정해진 이름의 메소드를 가지는 Statup 클래스를 통해 앱을 초기화하고 실행한다.

## Startup.ConfigureServices() 

여기서는 사용자가 앱에서 쓸 Pre-made Service들을 활성화하고 설정한다. 
Service에는 asp.net core에서 제공하는 것들(DB, Logging, Identity, Mvc)도 있지만, 
IEmailSender 같이 사용자가 만든 서비스들도 활성화할 수 있다 (Nancy와는 달리, 인터페이스를 통해서 하지 않고, 그냥 Reflection을 사용해서 초기화한다)

활성화한다는 것은.... 이 service들이 필요한 각 클래스들이 이 service들을 제공받을 수 (생성자를 통해.. 주로..) 있다는 의미. --> 의존성주입(Dependency Injection). --> 객체를 생성할 수 있는 "Container"에 타입을 등록하는 과정.

    - IServiceCollection의 AddSingletone<T>, AddTransient<T>, AddScoped<T> 등에 대한 내용

## Startup.Configure()


ConfigureServices()가 서비스를 활성화/등록하는 과정이이었다면, 실제로 앱이 해당 서비스를 쓰도록 만드는 부분은 Configure()메소드이다. 

### IHostingEnvironment.EnvironmentName

Configure() 시에 전달받는 IHostingEnvironment형 인자 env 는 

`env.IsDevleopment()` 라는 식으로 확장메소드를 통해 현재 환경이 "개발용:Development"인지 "현장용:Production" 인지를 알 수 있다. 개발시에 띄울 앱과 현장에서 실행될 앱과 조금 다르게 해야 하는 경우 많은 데, 그때 사용.

`env.IsDevelopment()` 는 다음코드와 동일하다.

```
env.EnvironementName == "Development"
```

그냥 문자열 비교이다. 그럼 이 EnvironmentName 이라는 문자열은 어디서 가져오는가?
그건 `appsettings.json` 파일이다. 그냥 


