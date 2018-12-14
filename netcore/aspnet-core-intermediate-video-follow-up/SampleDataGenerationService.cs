using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using mymva.Data;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace mymva
{
    public static class SampleDataGenerationService
    {
        public static void UseMyMvaAppSuperUser(this IApplicationBuilder app, string email, string password)
        {
            UseMyMvaAppSuperUserAsync(app, email, password).Wait();
        }

        private static async Task UseMyMvaAppSuperUserAsync(this IApplicationBuilder app, string email, string password)
        {
            var serviceProvider = app.ApplicationServices;
            var loggerFactory = serviceProvider.GetService<ILoggerFactory>();
            var logger = loggerFactory.CreateLogger(nameof(SampleDataGenerationService));
            using (var scope = serviceProvider.CreateScope())
            {
                // Admin
                // 여기 나와있는 코드를 설명할때는... Register.cshtml.cs 파일의 OnPose() 메소드를 보면서 설명했다. 
                // 
                logger.LogInformation("`Admin` and `Power User` roles 처리...");
                var roleManager = scope.ServiceProvider.GetService<RoleManager<IdentityRole>>();
                var adminRole = await roleManager.FindByNameAsync("Admin");
                if (adminRole == null)
                {
                    adminRole = new IdentityRole("Admin");
                    await roleManager.CreateAsync(adminRole);
                }

                var powerUserRole = await roleManager.FindByNameAsync("Power User");
                if (powerUserRole == null)
                {
                    powerUserRole = new IdentityRole("Power User");
                    await roleManager.CreateAsync(powerUserRole);
                }
            
                logger.LogInformation("(개발자용) super user 계정을 처리: {0}/{1}", email, password);
                var userManager = scope.ServiceProvider.GetService<UserManager<ApplicationUser>>();
                logger.LogInformation("UserManager.SupportsUserRole={0}", userManager.SupportsUserRole);

                var user = await userManager.FindByEmailAsync(email);
                if (user == null)
                {
                    user = new ApplicationUser
                    {
                        Email = email,
                        UserName = email,
                    };
                    await userManager.CreateAsync(user, password);
                }

                logger.LogInformation("super user 계정 Admin 권한설정 처리...");
                if (!await userManager.IsInRoleAsync(user, adminRole.Name))
                {
                    var result = await userManager.AddToRoleAsync(user, adminRole.Name);
                    logger.LogInformation("권한설정 결과 : {0}", result);
                }

                var userClaims = await userManager.GetClaimsAsync(user);
                var countryClaim = userClaims?.FirstOrDefault(claim => claim.Type == ClaimTypes.Country);
                if (countryClaim == null || countryClaim.Value != "Korea")
                {
                    if (countryClaim != null)
                    {
                        logger.LogInformation("이전의 Country Claim을 제거 : {0}", countryClaim);
                        await userManager.RemoveClaimAsync(user, countryClaim);
                    }

                    countryClaim = new Claim(ClaimTypes.Country, "Korea");
                    logger.LogInformation("새로운 Country Claim 주가 : {0}", countryClaim);
                    await userManager.AddClaimAsync(user, countryClaim);
                }
                
            }
        }
    }
}