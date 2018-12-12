using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace hello_razor
{
    public class HelloRazorAppConfigurator
    {
        public HelloRazorAppConfigurator(
            IConfiguration configuration,
            IHostingEnvironment hostingEnvironment,
            ILogger<HelloRazorAppConfigurator> logger
            )
        {
            Configuration = configuration;

            _env = hostingEnvironment;
            _logger = logger;
        }

        public IConfiguration Configuration { get; }
        private IHostingEnvironment _env;
        private ILogger<HelloRazorAppConfigurator> _logger;

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            _logger.LogInformation("ASPNETCORE_ENVIRONMENT : {0}", _env.EnvironmentName);
            _logger.LogWarning("LogLevel = {0}", Configuration["Logging:LogLevel:Default"]);
            var connectionString = Configuration["ConnectionString"];
            _logger.LogInformation("ConnectionString : {0}", connectionString);

            // 간단하게 서비스를 아래와 같이 등록할 수 있음(주로 사용자 정의 서비스)
            // services.AddSingleton<IEmailSender, EmailSender>();
            // services.AddTransient<IEmailSender, EmailSender>();
            // services.AddScoped<IEmailSender, EmailSender>();

            services.Configure<CookiePolicyOptions>(options =>
            {
                // This lambda determines whether user consent for non-essential cookies is needed for a given request.
                options.CheckConsentNeeded = context => true;
                options.MinimumSameSitePolicy = SameSiteMode.None;
            });


            services.AddMvc().SetCompatibilityVersion(CompatibilityVersion.Version_2_2);
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        // 주로 middleware 설정인데,... 순서가 중요.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if(env.IsEnvironment("Development"))  //if (env.IsDevelopment())  와 동일한 효과.
            {
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Error");
                // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
                app.UseHsts();
            }

            app.Use(async (context, next) =>
            {
                if (context.Request.Path == "/conf")
                {
                    await context.Response.WriteAsync("Hello .NET Conf");
                }
                else
                {
                    try
                    {
                        await next();   
                    }
                    catch (Exception ex)
                    {
                        // TODO show any error
                        throw;
                    }
                }
            });

            app.UseHttpsRedirection();
            app.UseStaticFiles();
            app.UseCookiePolicy();

            app.UseMvc();
        }
    }
}
