import { Component, OnInit, Input, Output, EventEmitter} from '@angular/core';

@Component({
  selector: 'app-item',
  templateUrl: './item.component.html',
  styleUrls: ['./item.component.css']
})
export class ItemComponent implements OnInit {
  @Input() character;
  @Input() iColor;

  @Output() sideAssigned = new EventEmitter<{name: string, side: string}>();

  onAssign(forceSide){
    //this.character.side = forceSide;
    this.sideAssigned.emit({name: this.character.name, side: forceSide});
  }

  constructor() { }

  ngOnInit() {
  }

}
