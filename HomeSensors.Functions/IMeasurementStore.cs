using HomeSensors.Functions.Domain;
using System.Threading.Tasks;

namespace HomeSensors.Functions;

public interface IMeasurementStore
{
    Task Persist(string sensorId, Measurement measurement);
}
