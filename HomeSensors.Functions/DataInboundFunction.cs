using HomeSensors.Functions.Inbound;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.IO;
using System.Threading.Tasks;

namespace HomeSensors.Functions
{
    public class DataInboundFunction
    {
        public DataInboundFunction()
        {
        }

        [FunctionName("data")]
        public async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            string requestBody = await new StreamReader(req.Body).ReadToEndAsync();
            var data = JsonConvert.DeserializeObject<MeasurementRequest>(requestBody);

            log.LogInformation("Reiceived sensor values: {Data}", data.ToJson());

            var measurement = data.ToDomain();

            return new OkResult();
        }
    }
}
