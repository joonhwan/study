using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Razor.TagHelpers;

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
