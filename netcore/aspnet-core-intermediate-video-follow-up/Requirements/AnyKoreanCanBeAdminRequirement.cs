using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.Extensions.Logging;

namespace mymva.Requirements
{
    public class AnyKoreanCanBeAdminRequirement : AuthorizationHandler<AnyKoreanCanBeAdminRequirement>, IAuthorizationRequirement
    {
        private ILogger _logger;

        public AnyKoreanCanBeAdminRequirement(ILoggerFactory loggerFactory)
        {
            _logger = loggerFactory.CreateLogger(nameof(AnyKoreanCanBeAdminRequirement));
        }
        
        protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, AnyKoreanCanBeAdminRequirement requirement)
        {
            _logger.LogInformation("AnyKoreanCanBeAdminRequirement 가 Requirement 처리중 : User={0}", context.User);
                
            var claims = string.Join(",", context.User.Claims.Select(claim => $"{claim.Type}={claim.Value}"));
            _logger.LogInformation("확인된 Claim들 : {0}", claims);

            if (context.User.HasClaim(claim => claim.Type == ClaimTypes.Country && claim.Value == "Korea"))
            {
                _logger.LogInformation("사용자가 Korean이네.");
                context.Succeed(requirement);
            }
            else if (context.User.IsInRole("Admin"))
            {
                _logger.LogInformation("사용자가 Admin이네.");
                context.Succeed(requirement);
            }

            return Task.CompletedTask;
        }
    }
}
