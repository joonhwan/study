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

index.cshtml에 `@inject` 로 특정 타입을 주면 해당 페이지에 필요로 하는 서비가 주입된다. 이때, `Microsoft.Extensions.Configuration.IConfiguration`을 타입으로 준다. 이렇게 해서 appsettings.json파일 혹은 실행시키는 시스템의 환경변수값을 얻을 수 있다.

이를테면, index.cshtml파일을 다음처럼 바꾼다.

```html
@page
@using Microsoft.Extensions.Configuration
@model IndexModel
@inject IConfiguration Configuration
@{
    ViewData["Title"] = "Home page";
}

@*환경변수 "COMPUTERNAME"을 여기 출력할 수 있다(설정파일에는 없지만, 환경변수로는 있다!! 환경변수도 가져올 수 있다)*@
<h2>환경변수 COMPUTERNAME-의 값: @Configuration["computername"]</h2>

@*또는 appsettings.json에 포함시킨 설정값을 볼 수 도 있다*@
<h2>apsettings설정파일에 있는 MyTwitterKye값: @Configuration["MyTwitterKey"]</h2>
```

여기서 MyTwitterKey는 appsettings.json 파일에 다음처럼 기록

```json
{
  "ConnectionStrings": {
    "DefaultConnection": "DataSource=app.db"
  },
  "Logging": {
    "IncludeScopes": false,
    "LogLevel": {
      "Default": "Warning"
    }
  },
  "MyTwitterKey":  "Joonhwan" 
}
```

appsettings파일은 `appsettings.Development.json` 과 `appsettings.json` 이 있는데, 이 2개 파일은 override되는 거 같다. 예를들어 IHostingEnvironment.EnvironmentName 이 "Development"이면 `appsettings.Development.json`에서 "MyTwitterKey"를 찾는다. 그런다음, 거기 그런 값이 없으면, fallback config로 appsettings.json 에서 해당 이름의 값을 찾는식이다... 

그럼 대체 이 `EnvironmentName`은 어디서 설정가능한가?

   - 환경변수 `ASPNETCORE_ENVIRONMENT` (동영상에서 사용한 방법.)
   - `dotnet new`로 만든 프로젝트 코드의 ./properties/launchSettings.json

이 2곳에서 가능한것으로 보인다.

어쨌든 파일에다 트위터계정등과 같은 *민감한* 정보를 담아서 커밋하는건...찝찝하므로, `secrets.json` 같은 파일에 저장하는 방법이 소개되고 있다.

자세한 방법은 ["Safe storage of app secrets in development in ASP.NET Core" 문서](https://docs.microsoft.com/ko-kr/aspnet/core/security/app-secrets) 참고

간단히 설명하면 

   - `*.csproj` 파일에 `<UserSecretsId>` 태그 삽입하고 고유한아이값("user_secrets_id") 지정 - GUID같은게 포함되도록 하는게 좋겠지?
   - `%APPDATA%\Microsoft\UserSecrets\<user_secrets_id>\secrets.json` 파일에 민감한 정보 넣기.
    
사실. 첫번째것은 `dotnet new` 할때 이미 되어 있었던거 같다. 두번째의 `secrets.json`만 만들면 되는것 같다. 

`secrets.json` 말고 환경변수로 하는것도 안전할 수 있을거다. 환경변수가 모든걸 override한다! 

    설정 우선순위 : 환경변수 > secrets.json > appsettings.json

환경변수로 LogLevel값을 설정하려면 다음과 같이 한다.

```sh
> set Logging:LogLevel:Default=Info
```

즉, 계층구조로 되어 있는 json 설정구조를 콜론(`:`)을 사용해 표시할 수 있다.

동영상에서는 Application Insight로 로그를 보는 장면을 보여준다. aspnet core는 기본적으로 application insight에 로그 메시지를 보내 visual studio에서 이 로그들을 볼 수 있단다.


# TagHelper

먼가 가볍고 빠르고 좋단다. [doc.microsoft.com의 tag-helper 관련문서](https://docs.microsoft.com/ko-kr/aspnet/core/mvc/views/tag-helpers)를 보여주며 읽기 시

Razor라고 불리우는 html template markup (즉, html을 작성할때 *실행시*에 문서의 일부분이 자동으로 생성되도록 하는 마크업)을 c# 코드로 쉽게 작성할 수 있는....

*NOTE!: 조사해보니, TagHelper는 HtmlHelper라는 C#코드기반 Html생성기와는 함께 많이쓰인다. TagHelper는 html 태그처럼 작성되지만, HtmlHelper는 C#코드다.* 

TagHelper를 쓰려면, `cshtml` 파일내 혹은 다음 내용을 가지는 다른 `cshtml`(예: `_ViewImports.cshtml` 파일)을 *포함*시켜야 한다

```
@addTagHelper *, Microsoft.AspNetCore.Mvc.TagHelpers
```

`Register.cshtml` 파일을 열어서 마우스로 vs 2017 에디터에서 각 tag에 갖다대면 툴팁문서가 뜬다는걸 보여줌. 이어서, 실제로 이 페이지가 실제 html로 어떻게 만들어지는지 결과물을 소스코드와 함께 비교해서 봄.

```html

<div class="row">
    <div class="col-md-4">
        <form asp-route-returnUrl="@Model.ReturnUrl" method="post">
            <h4>Create a new account.</h4>
            <hr />
            <div asp-validation-summary="All" class="text-danger"></div>
            <div class="form-group">
                <label asp-for="Input.Email"></label>
                <input asp-for="Input.Email" class="form-control" />
                <span asp-validation-for="Input.Email" class="text-danger"></span>
            </div>
            <div class="form-group">
                <label asp-for="Input.Password"></label>
                <input asp-for="Input.Password" class="form-control" />
                <span asp-validation-for="Input.Password" class="text-danger"></span>
            </div>
            <div class="form-group">
                <label asp-for="Input.ConfirmPassword"></label>
                <input asp-for="Input.ConfirmPassword" class="form-control" />
                <span asp-validation-for="Input.ConfirmPassword" class="text-danger"></span>
            </div>
            <button type="submit" class="btn btn-default">Register</button>
        </form>
    </div>
</div>
```
위와 같은 html 문서에서 거의 모든부분(asp-* 로 시작하는 속성뿐 아니라 표준 form태그도  TagHelper로 구현됨.  cf: div, button 같은건 TagHelper가 아닌듯..)

또, \_Layout.cshtml 파일을 열어서 ...

```html
    <environment include="Development">
        <link rel="stylesheet" href="~/lib/bootstrap/dist/css/bootstrap.css" />
        <link rel="stylesheet" href="~/css/site.css" />
    </environment>
    <environment exclude="Development">
        <link rel="stylesheet" href="https://ajax.aspnetcdn.com/ajax/bootstrap/3.3.7/css/bootstrap.min.css"
              asp-fallback-href="~/lib/bootstrap/dist/css/bootstrap.min.css"
              asp-fallback-test-class="sr-only" asp-fallback-test-property="position" asp-fallback-test-value="absolute" />
        <link rel="stylesheet" href="~/css/site.min.css" asp-append-version="true" />
    </environment>
```

`environment` 태그가 TagHelper로 구현되어 있음을 보여줌. 이 태그는 EnvironmentName이 "Development"면 최종 출력 HTML에 하위 태그들을 포함 하기도/안하기도 하도록 만들어줌.

TagHelper 안에 또 TagHelper를 넣을 수 있다고 설명.

[BuiltIn TagHelper에 대해 공식문서](https://docs.microsoft.com/ko-kr/aspnet/core/mvc/views/tag-helpers/built-in)를 보여줌.

*_VewImports.cshtml* 에 저장된 `addTagHelpers` 구문을 강조한다음, TagHelper를 직접 만들어본다.

새로 RepeatTagHelerp.cs 를 만들었다.

```csharp
//...
namespace mymva
{
    public class RepeatTagHelper : TagHelper
    {
        public int Count { get; set; }

        public override async Task ProcessAsync(TagHelperContext context, TagHelperOutput output)
        {
            for (int i = 0; i < Count; i++)
            {
                var children = await output.GetChildContentAsync(useCachedResult: false);
                output.Content.AppendHtml(children);
            }
        }
    }
}
```

그리고, TagHelper를 `_ViewImports.cs` 에서 등록했음.

```
@using Microsoft.AspNetCore.Identity
@using mymva
@using mymva.Data
@namespace mymva.Pages
@addTagHelper *, Microsoft.AspNetCore.Mvc.TagHelpers
@addTagHelper *, mymva
```

이런식으로 유용한 TagHelper를 만들어 라이브러리로 배포하는 사람이 있단다.( [TagHelperPack - Github](https://github.com/DamianEdwards/TagHelperPack) ). 이 라이브러리를 참고하서 자신만의 Customized된 TagHelper를 만들어보는걸 추천?하는 것 같다.

또다른 TagHelper 라이브러리 소개 : [TagHelperSamples - Github](https://github.com/dpaquette/TagHelperSamples). 특히 어떻게 평범한 `div` 태그로 확장되는 TagHelper를 만들수 있는지를 [ProgressBarTagHelper.cs](https://github.com/dpaquette/TagHelperSamples/blob/master/TagHelperSamples/src/TagHelperSamples.Bootstrap/ProgressBarTagHelper.cs) 를 보여주며 설명. 

```csharp
// ...
   [HtmlTargetElement("div", Attributes = ProgressValueAttributeName)]
   public class ProgressBarTagHelper : TagHelper
   {
      private const string ProgressValueAttributeName = "bs-progress-value";
      private const string ProgressMinAttributeName = "bs-progress-min";
      private const string ProgressMaxAttributeName = "bs-progress-max";
//...
```
위를 보면, `HtmlTargetElement` 어트리뷰트로 `div` 태그가 되도록 설정한거를 설명.

그리고, 사람들이 WEB UI만들때 Bootstrap을 많이 쓰는데, 아예 Bootstrap TagHelper 같은 걸 찾아서 쓰면 HTML 작성하는 과정이나 가독성이 훨씬 좋아지는 그런걸 얘기한다.
(예를들어, [Bocons - Github](https://github.com/brecons/bootstrap-tag-helper) 같은 라이브러리..)

# 인증(Autthentication: 너 누구냐)과 권한(Authorization: 넌 그거 할 수 없어/있어)

로그인과 관련된 내용. 주로 Identity 서비스(Microsoft.AspNetCore.Identity) 관련된 내용.

그런데... 로그인하고, 비밀번호 잊으면 메일보내고, 이중 인증(스마트폰 어플등으로 QR코드등 입력받아서...)하고 이런거에 대한 설명. 

또 Google/Facebook/Twitter/MS 같은 걸 통해서 인증하는 절차설명(일단 나는 이런게 필요없어서 스킵)

`PageModel` 파생 클래스들에 `[Authorize(Role = "Admin")]` 과 같은 속성을 주어서 특정 페이지가 특정권한을 가지는 사람들에게만 허용되도록 하는 걸 보여줌. (신기한건 그냥 `[Authorize]` 라는 속성만 주면, 로그인이 된 사용자에게만 허용되게 한다..는거.)
아울러 코드로 사용자를 생성하고, 권한을 주는걸 설명함. 


권한설정뿐 아니라 정책(Policy)에 대해서도 설명 : 예로 "캐나다"사람들에게만 특정 기능을 허용.  국가를 인식하는 웹상의 공통된 기술이 있는것 같다. 사용자 정보에게 굳이 국가를 적지 않아도 되나보다. 이런걸 하는 걸 "특정사용자에게 AddClaim()한다..."라고 생각할것.

디폴트로는 Claim(=Policy)와 Role은 모두 "AND"로 적용된다.  이걸 "OR"하려면, `AuthorizationHandler<T>` 를 상속받아 Custom Handler를 작성해야 하고, 인증미들웨어에 어떤식으로든 추가되도록 한다. 모든 policy은 각자의 이름을 가지고. `PageModel` 상속 클래스에서는 이 속성이 `[Authorize(Policy = "CanadiansOnlyOrAdmin")]` 같이 이름을 지정만 하면 된다. 

`*.cshtml` 파일에 `IAuthorizationService` 를 inject하여 특정 html tag가 로그인상태.권한등 상태에 따라 표시되기도 하고 안되기도 하는 걸 보여줌.





