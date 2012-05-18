package main

import (
	"time"
	"fmt"
	"math"
)

func main() {
	knownNew, _ := time.Parse("2006-01-02 15:04", "1999-08-11 00:00")
	daysSince := float64(time.Now().Sub(knownNew)) / float64(time.Hour) / 24
	
	phase := math.Mod(float64(daysSince), 29.530588853)

	switch {
	case phase < 1.84566:
		fmt.Println("New")
	case phase < 5.53699:
		fmt.Println("Waxing crescent")
	case phase < 9.22831:
		fmt.Println("First quarter")
	case phase < 12.91963:
		fmt.Println("Waxing gibbous")
	case phase < 16.61096:
		fmt.Println("Full")
	case phase < 20.30228:
		fmt.Println("Waning gibbous")
	case phase < 23.99361:
		fmt.Println("Last quarter")
	case phase < 27.68493:
		fmt.Println("Waning crescent")
	default:
		fmt.Println("New")
	}

	return
}

