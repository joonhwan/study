# dotnet new webapp  으로 부터 razor page app 만들어보기.

- 공부한 동영상 : [Code Camp 2018 - Introduction to Razor Pages](https://youtu.be/2ov3C_fn6s8?t=506)
- client web asset(css/js/font/image..)의 관리를 위해 npm 을 사용법 : [블로그 문서](https://blogs.taiga.nl/martijn/2017/11/24/building-and-asp-net-core-mvc-app-with-npm-and-webpack-asp-net-core-2-0-edition/)

# 만든 수순
  - 다른 예제와는 달리 netcore 2.2 sdk를 사용해보았기 때문에, global.json에 2.2.100 을 일단 기록해 놓음.
  - npm 관련된 거는 상기 블로그 문서의 내용을 따라함.
    - 사용할 의존성 있는 클라이언트측 js 라이브러리들은 main.js 파일에 기록(블로그에서는 별도의 폴더를 만듬)
  - 급변하는 웹 클라이언트 세계의 특성때문에 다음 부분을 추가 수정
    - UglifyJsPlugin 관련 수정 (optimization.minimize 부분과 함께 본다)
    - bootstrap이 popper.js가 없다고 함. `npm i --save popper.js` 한다.
    - jquery의 $ 전역 심볼이 정의가 안되는 문제 : 위 블로그의 댓글을 보고 `npm i --save-dev expose-loader` 한다음 `webpack.config.js` 수정.
  - Pages 폴더생성하고.. Index.cshtml 을 만들어봄. --> 잘되는 거 확인하고, 기존 razor app 처럼 _Layout, _ViewStart, _ViewImport를 만든다.
  - _Layout, _ViewStart,.. 등과 같은 얘들에 대한 설명은... [C#Sharp Corner](https://www.c-sharpcorner.com/blogs/layouts-and-viewstartcshtml-in-mvc) 에 설명이 있어 읽어보았다. 파일의 위치는 convention이 있지만, 나는 그냥 Pages 폴더안에 다 넣었다(_ViewStart.cshtml 내용 확인)
   - `dotnet publish -c Release -o .publish` 하면 `./.publish` 폴더내에 배포할 파일이 모인다. 
  
# 빌드

  - `npm build` : 이걸 해야 js/css 등이 bundling되어 wwwroot/dist 폴더내에 쌓인다("번들링"). cshtml에서는 여기의 파일을 로드한다.
  - `dotnet build` 

참고로 `dotnet publish`는 csproj 파일내에 별도의 타겟이 지정되어 있어서, publish 될 폴더로 번들링 된 파일들이 복사된다.

    
