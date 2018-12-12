using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;

namespace hello_razor
{
    public class Program
    {
        public static void Main(string[] args)
        {
            CreateWebHostBuilder(args).Build().Run();
        }

        public static IWebHostBuilder CreateWebHostBuilder(string[] args) =>
            WebHost.CreateDefaultBuilder(args)
                // 실제로 아래와 같은 내용(정확히 같지는 않아도..) DefaultBuilder 만들때 수행된단다. 자신만의 설정을 만들때는 아래 주석 참고.
                // .ConfigureAppConfiguration((context, configBuilder) => {
                //     configBuilder.AddJsonFile("appsettings.json");
                //     configBuilder.AddJsonFile($"appsettings.{context.HostingEnvironment.EnvironmentName}.json", optional: true);
                // })
                // .ConfigureLogging((context, loggingBuilder) => {
                //     loggingBuilder.AddConfiguration(context.Configuration);
                //     loggingBuilder.AddDebug();
                //     loggingBuilder.AddConsole();
                // })
                .UseStartup<HelloRazorAppConfigurator>();
    }
}
