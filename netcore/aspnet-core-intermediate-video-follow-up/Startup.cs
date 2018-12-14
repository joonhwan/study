using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using mymva.Data;
using mymva.Requirements;
using mymva.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.Extensions.Logging;

namespace mymva
{
    public class Startup
    {
        private ILoggerFactory _loggerFactory;

        public Startup(IConfiguration configuration, ILoggerFactory loggerFactory)
        {
            Configuration = configuration;
            _loggerFactory = loggerFactory;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddDbContext<ApplicationDbContext>(options =>
                options.UseSqlite(Configuration.GetConnectionString("DefaultConnection")));

            services
                // UserManager와 SignInManager등 Identity 서비스에서 제공하는 클래스들을 주입받을 수 있다.
                // Register.cshtml.cs 참고.
                .AddIdentity<ApplicationUser, IdentityRole>()
                // AddIdentity() 가 반환하는 IdentityBuilder객체를 통해 Identity가 사용할 저장소를 설정한다.
                .AddEntityFrameworkStores<ApplicationDbContext>()
                // AddEntityFrameworkStores() 확장메소드는 계속 IdentityBuilder를 반환하는 Fluent API . 추가적으로 이런저런 설정..
                .AddDefaultTokenProviders()
                ;

            var anyKoreanCanBeAdminRequirement = new AnyKoreanCanBeAdminRequirement(_loggerFactory);

            services.AddAuthorization(options =>
            {
                options.AddPolicy("CandianAdminsOnly", builder => builder
                    .RequireClaim(ClaimTypes.Country, "Canada")
                    .RequireClaim(ClaimTypes.Role, "Admin")
                );
                options.AddPolicy("KoreanAdminsOnly", builder => builder
                    .RequireClaim(ClaimTypes.Country, "Korea")
                    .RequireClaim(ClaimTypes.Role, "Admin")
                );
                options.AddPolicy("AnyKoreanCanBeAdminRequirement", builder => builder.AddRequirements(anyKoreanCanBeAdminRequirement));
            });

            services
                // 만들때 dotnet new razor 했지만, 이게 결국 mvc 위에서 만들어지거기 때문에, mvc서비스를 활성화 하고. 
                // AddMvc()가 반환하는 IMvcBuilder 를 통해 Razor기능을 또 활성화하는 식이다. razor app에서도 여전히 mvc를 쓸 수 있단다(web api용등)
                .AddMvc()
                .AddRazorPagesOptions(options =>
                {
                    options.Conventions.AuthorizeFolder("/Account/Manage");
                    options.Conventions.AuthorizePage("/Account/Logout");
                });

            // Register no-op EmailSender used by account confirmation and password reset during development
            // For more information on how to enable account confirmation and password reset please visit https://go.microsoft.com/fwlink/?LinkID=532713
            services.AddSingleton<IEmailSender, EmailSender>();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.

        // 여기에서는 순서가 중요한다.
        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
                app.UseDatabaseErrorPage();
            }
            else
            {
                app.UseExceptionHandler("/Error");
            }

            app.UseStaticFiles();

            app.UseAuthentication();
            if (env.IsDevelopment())
            {
                app.UseMyMvaAppSuperUser("dev@test.com", @"Passw0rd!");
            }

            app.UseMvc(routes =>
            {
                routes.MapRoute(
                    name: "default",
                    template: "{controller}/{action=Index}/{id?}");
            });
        }
    }
}
