using HomeSensors.Functions.Domain;
using System.Threading.Tasks;

namespace HomeSensors.Functions.Persistance
{
    public class SqlStore : IMeasurementStore
    {
        public Task Persist(string sensorId, Measurement measurement)
        {
            throw new System.NotImplementedException();
        }
    }
}
