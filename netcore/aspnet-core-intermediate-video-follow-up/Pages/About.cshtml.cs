using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace mymva.Pages
{
    [Authorize(Policy = "AnyKoreanCanBeAdminRequirement")]
    //[Authorize(Policy = "KoreanAdminsOnly")]
    //[Authorize(Policy = "CandianAdminsOnly")]
    //[Authorize(Roles = "Admin")]
    public class AboutModel : PageModel
    {
        public string Message { get; set; }

        public void OnGet()
        {
            Message = "Your application description page.";
        }
    }
}
