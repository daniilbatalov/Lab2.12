#ifndef FLIGHT_H
#define FLIGHT_H

#include <QDate>

class Flight
{
private:
    QDate m_departureDate;
    QTime m_departureTime;
    QTime m_flightTime;
    bool m_breakfast;
    QString m_airport;
public:
    QDate getDepartureDate() const;
    void setDepartureDate(const QDate&);
    QTime getDepartureTime() const;
    void setDepartureTime(const QTime&);
    QTime getFlightTime() const;
    void setFlightTime(const QTime&);
    bool getBreakfast() const;
    void setBreakfast(const bool);
    QString getAirport() const;
    void setAirport(const QString);
    void breakfast_check();
    Flight(const QDate&, const QTime&, const QTime&, const QString);
};

#endif // FLIGHT_H
