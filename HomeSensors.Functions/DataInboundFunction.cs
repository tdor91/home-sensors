using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using HomeSensors.Functions.Inbound;

namespace HomeSensors.Functions
{
    public class DataInboundFunction
    {
        public DataInboundFunction()
        {
        }

        [FunctionName("data")]
        public async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "post", Route = null)] MeasurementRequest request,
            ILogger log)
        {
            log.LogInformation("Reiceived sensor values. {Data}", request.ToJson());
            return new OkResult();
        }
    }
}
